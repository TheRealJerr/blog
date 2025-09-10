#include <iostream>
#include <unordered_map>
#include <boost/asio.hpp>
// 构建普通的功能
// 字典的功能
class Service
{
public:
    std::string apply(const std::string& key) 
    {
        if(_dics.count(key)) return _dics[key];
        else return "no Service";
    }
private:
    std::unordered_map<std::string,std::string> _dics = 
    {
        {"hello", "world"}
    };
};
namespace net = boost::asio;
namespace system = boost::system;

// 构建一次会话的连接
class Session : public std::enable_shared_from_this<Session>
{
public:

    // 事件就绪, 进行读操作
    void read()
    {
        auto self = shared_from_this();
        auto handler = [this, self = std::move(self)](system::error_code ec, size_t lenth)
        {
            // 这个时候应该已经读到了 buffer中
            std::string str;
            std::copy(buffer_.begin(), buffer_.end(), std::back_inserter(str));
            std::cout << "收到的数据" <<  str << std::endl;
            // 调用服务
            auto rsp = service_.apply(str);

            write();
        };
        socket_.async_read_some(net::buffer(buffer_), handler);
        read();
    }

    void write()
    {
        socket_.async_write_some()
    }
private:
    net::ip::tcp::socket socket_; // 通信连接
    std::vector<char> buffer_; // 通过vector持有数据

    // 字典服务
    Service service_;
};