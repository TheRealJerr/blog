#include <jsoncpp/json/json.h>
#include <iostream>
#include <sstream>
using namespace Json;

void testJson()
{
    Value val;
    val["name"] = "hrj";
    val["age"] = 18;
    Value t;
    t["hello"] = "world";
    val["info"] = t;
    val["t"].append(1);
    val["t"].append("hello world");
    StreamWriterBuilder builder;
    auto* writer = builder.newStreamWriter();
    std::stringstream ssm;
    writer->write(val,&ssm);
    std::cout << ssm.str() << std::endl;
}

void testRedis_2()
{
    std::string str_json = R"({
            "age" : 18,
            "info" : 
            {
                    "hello" : "world"
            },
            "name" : "hrj",
            "t" : 
            [
                    1,
                    "hello world"
            ]
        })";
    }
auto main() -> int
{
    testJson();
    return 0;
}