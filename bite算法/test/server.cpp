
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
#include <cstring>
#include <string>

class Server
{
public:
    Server(uint16_t port)
    {
        _sockfd = ::socket(AF_INET, SOCK_DGRAM, 0);
        
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = ::htons(port);
        int n = ::bind(_sockfd, (struct sockaddr*)(&addr), sizeof(addr));
        if(n < 0)
        {
            std::cerr << "bind error : " << strerror(errno) << std::endl;
            ::exit(1);
        }
        else std::cerr << "bind sucessfully" << std::endl;

        //

    }

    void start()
    {
        
    }
private:
    int _sockfd;
};