// 复习通过udp进行连接

#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
#include <cstring>
#include <string>
class Client
{
public:

    Client(const std::string& ip,uint16_t port)
    {
        _sockfd = ::socket(AF_INET, SOCK_DGRAM, 0);
        if(_sockfd < 0)
        {
            std::cerr << "sock create fail! : " << strerror(errno) << std::endl;
            ::exit(1);
        }
    }
    void send(const std::string&,const std::string&,uint16_t);

    void read(std::string* ,std::string*, uint16_t*);


private:
    int _sockfd;
};

void Client::send(const std::string& msg,const std::string& ip,uint16_t port)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = ::inet_addr(ip.c_str());
    addr.sin_port = ::htons(port);
    int n = ::sendto(_sockfd, msg.c_str(),msg.size(),0, (struct sockaddr*)(&addr),sizeof(addr));
    if(n < 0)
    {
        std::cerr << "send error: " << strerror(errno) << std::endl;
    }else std::cerr << "send sucessfully" << std::endl;
}

void Client::read(std::string* msg, std::string* ip, uint16_t* port)
{
    struct sockaddr_in sock_addr;
    socklen_t sock_len;
    char* buffer[1024] = { 0 };
    int n = ::recvfrom(_sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)(&sock_addr), &sock_len);
    if(n < 0)
    {
        std::cerr << "receive error: " << strerror(errno) << std::endl;
    }
    else
    {
        buffer[n] = 0;
        msg->append((char*)(buffer));
        *ip = ::inet_ntoa(sock_addr.sin_addr);
        *port = ::ntohs(sock_addr.sin_port);
    }
}