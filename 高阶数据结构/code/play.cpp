#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
extern char** environ;
#include <sys/epoll.h>
auto main() -> int
{
    for(int i = 0; environ[i];i++)
    {
        std::cout << environ[i] << std::endl;
    }
    pid_t pid = ::fork();
    if(pid == 0)
    {
        // 表示是子进程
        
    }
    
    else 
    {
        // 表示是父进程
        waitpid(pid,nullptr,0);
        printf("等待成功\n");
    }
    return 0;    
}