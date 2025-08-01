#include <iostream>
#include <cerrno>
#include <cstring>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <fstream>
enum 
{
    INPUT_ERR,
    TOUCH_ERR,
    FILEOPEN_ERR,
};

void Usage(int argc)
{
    std::cout << "Usage Input:" << argc << std::endl;
    ::exit(INPUT_ERR);
}
std::string getCurTime()
{
    auto now = std::chrono::system_clock::now();

    // 转换为 time_t
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

    // 转换为本地时间
    std::tm now_tm = *std::localtime(&now_time_t);

    // 获取毫秒部分
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()
    ) % 1000;

    std::stringstream ssm;
    // 格式化输出时间
    ssm << "Current time: "
              << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S")
              << "." << std::setfill('0') << std::setw(3) << milliseconds.count();
    return ssm.str();
}

void WriteDateIntoFile(const std::string& filename)
{
    std::ofstream ofs(filename);
    if(ofs.is_open() == false)
    {
        std::cerr << "open " << filename << " fail:" << strerror(errno) << std::endl;
        ::exit(FILEOPEN_ERR);
    }

    ofs << "// create by hrj" << std::endl;
    ofs << "// " << getCurTime() << std::endl;
    ofs << "#include \"/home/hrj/leetcode/headFile.h\"" << std::endl;
}

bool TouchNewFile(const std::string& filename)
{
    // 通过子进程创建
    pid_t pid = ::fork();
    ::chdir("/home/hrj/leetcode/");
    if(pid == 0)
    {
        // 子进程
        int ret = ::execlp("touch","touch",filename.c_str(), nullptr);
        if(ret < 0)
        {
            std::cerr << strerror(errno) << std::endl;
            exit(TOUCH_ERR);
        }
    }  
    else 
    {
        // 主线程
        pid_t tid = ::waitpid(pid,nullptr,0); // 阻塞等待
        if(tid > 0)
        {
            std::cout << "wait successfully" << std::endl;
        }
        WriteDateIntoFile(filename);
    }
    return true;
}
int main(int argc,char* argv[])
{
    if(argc != 2) Usage(argc);
    std::string filename = argv[1];
   
    bool ret = TouchNewFile(filename);
    if(ret) std::cout << "create " << filename << " sucessfully" << std::endl;
    else std::cout << "create " << filename << " fail!" << std::endl;
    return 0;
}
