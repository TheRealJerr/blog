#include <sw/redis++/redis++.h>
#include <iostream>
#include <vector>
using Server_t = std::unique_ptr<sw::redis::Redis>;

Server_t initRedisServer(const std::string& ip, uint16_t port)
{
    std::string cmd = "tcp://" + ip + ":" + std::to_string(port);
    return std::make_unique<sw::redis::Redis>(cmd);
}

void testRedis()
{
    try{
        Server_t server = initRedisServer("127.0.0.1", 6379);

        server->hset("runoobkey", "new", "from task");
        
        std::vector<std::string> output;
        server->keys("*",std::back_inserter(output));
        for(auto& str : output)
            std::cout << str << std::endl;
    } catch(const sw::redis::Error& e)
    {
        std::cout << "redis Error:" << e.what() << std::endl;
    } catch(...)
    {
        std::cout << "未知的异常" << std::endl;
    }
}
auto main() -> int
{
    
    return 0;
}