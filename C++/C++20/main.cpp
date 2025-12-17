// 编译运行以下代码以后，客户端使用一个telnet localhost 9000就可以进行测试
#include <iostream>
#include <coroutine>
#include <thread>
#include <vector>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
#include <memory>
#include <array>

// 将文件描述符设置为非阻塞模式
static void set_nonblocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0); // 获取当前文件状态标志
    if (flags == -1) {
        perror("fcntl F_GETFL");
        return;
    }
    // 添加非阻塞标志
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl F_SETFL O_NONBLOCK");
    }
}

// I/O 等待器：用于协程等待 epoll 事件
struct IoAwaiter {
    int fd;         // 要等待的文件描述符
    int events;     // 要等待的事件类型：EPOLLIN(可读) 或 EPOLLOUT(可写)
    epoll_event ev{}; // epoll 事件结构

    // 静态成员，保存 epoll 实例的文件描述符
    static inline int epfd = -1;

    // 协程等待开始前调用
    // 返回 false 表示需要挂起等待
    bool await_ready() const noexcept {
        return false;
    }

    // 挂起协程，并将事件注册到 epoll
    void await_suspend(std::coroutine_handle<> h) noexcept {
        // 将协程句柄存到 epoll_event 的 data.ptr 中
        ev.data.ptr = h.address();
        // 设置事件类型，并使用边缘触发(EPOLLET)
        ev.events = events | EPOLLET;
        // 将 fd 和事件注册到 epoll
        epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);
    }

    // 协程恢复后调用
    // 从 epoll 中移除该事件
    void await_resume() noexcept {
        epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &ev);
    }
};

// 等待 accept 事件的协程等待器
IoAwaiter co_accept(int fd) {
    return IoAwaiter{ fd, EPOLLIN };
}

// 等待读事件的协程等待器
IoAwaiter co_read(int fd) {
    return IoAwaiter{ fd, EPOLLIN };
}

// 等待写事件的协程等待器
IoAwaiter co_write(int fd) {
    return IoAwaiter{ fd, EPOLLOUT };
}

// 协程任务类型
struct Task {
    struct promise_type {
        // 返回协程对象
        Task get_return_object() { return {}; }
        // 初始不挂起
        std::suspend_never initial_suspend() noexcept { return {}; }
        // 结束不挂起
        std::suspend_never final_suspend() noexcept { return {}; }
        // 协程返回 void
        void return_void() {}
        // 异常处理
        void unhandled_exception() { std::terminate(); }
    };
};

// 每个客户端连接的处理协程
Task echo_session(int sock) {
    try {
        std::array<char, 4096> buf; // 缓冲区
        for (;;) {
            // 等待 socket 可读
            co_await co_read(sock);

            // 读取数据
            ssize_t n = read(sock, buf.data(), buf.size());
            if (n <= 0) {
                // 连接关闭或出错
                if (n < 0) perror("read");
                break;
            }

            // 等待 socket 可写
            co_await co_write(sock);

            // 回写数据
            write(sock, buf.data(), n);
        }
    }
    catch (...) {
        std::cerr << "Session error\n";
    }
    close(sock); // 关闭连接
}

// 监听协程：接受新连接并创建会话协程
Task listener(int port) {
    // 创建监听 socket
    int s = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (s < 0) { perror("socket"); co_return; }

    // 设置 socket 选项：允许地址重用
    int opt = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 绑定地址和端口
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY; // 监听所有网卡
    addr.sin_port = htons(port);       // 端口号

    if (bind(s, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        co_return;
    }

    // 开始监听
    if (listen(s, SOMAXCONN) < 0) {
        perror("listen");
        co_return;
    }

    std::cout << "Listening on port " << port << std::endl;

    // 循环接受新连接
    for (;;) {
        // 等待监听 socket 可读（有新连接）
        co_await co_accept(s);

        // 接受连接
        sockaddr_in peer{};
        socklen_t len = sizeof(peer);
        int client = accept4(s, (sockaddr*)&peer, &len, SOCK_NONBLOCK);
        if (client < 0) {
            if (errno != EAGAIN && errno != EWOULDBLOCK) {
                perror("accept");
            }
            continue;
        }

        std::cout << "New connection from " << inet_ntoa(peer.sin_addr) << std::endl;

        // 为新连接创建会话协程
        echo_session(client);
    }
}

int main() {
    // 创建 epoll 实例
    IoAwaiter::epfd = epoll_create1(0);
    if (IoAwaiter::epfd < 0) {
        perror("epoll_create1");
        return 1;
    }

    // 启动监听协程
    listener(9000);

    // 事件循环
    std::vector<epoll_event> events(64); // 事件数组
    for (;;) {
        // 等待事件发生
        int nfds = epoll_wait(IoAwaiter::epfd, events.data(), events.size(), -1);
        if (nfds < 0) {
            perror("epoll_wait");
            break;
        }

        // 处理每个就绪事件
        for (int i = 0; i < nfds; ++i) {
            // 从事件中取出协程句柄并恢复执行
            std::cout << "eventfd:" << i << " 就绪, events:" << events[i].events << std::endl;
            auto h = std::coroutine_handle<>::from_address(events[i].data.ptr);
            h.resume();
        }
    }
}