#include <iostream>
#include <mysql-cppconn/mysqlx/xdevapi.h>
using namespace mysqlx;

using Session_t = std::unique_ptr<Session>;


// 创建一个会话
Session_t createSession(const std::string& ip,
    const std::string& usrname, 
    const std::string& passwd,
    const std::string& database,
    int port = 33060) // x api默认的端口包
{
    SessionSettings setting(
        SessionOption::HOST, ip,
        SessionOption::PORT, port,
        SessionOption::USER, usrname,
        SessionOption::PWD, passwd,
        SessionOption::DB, database
    );
    // 通过unique_ptr进行管理
    return std::make_unique<Session>(setting);
}

// nosql的风格
void NoSQLField(Session_t& session)
{
    // 获取对应表单
    Schema schema = session->getSchema("user_db");
    Collection coll = schema.getCollection("account");
    //
    // 这是一种类似Json的风格
    coll.add(R"({
        "id" : 3, 
        "name": "hehe",
        "balance" : 100 
        })").execute(); 
    

    DocResult doc = coll.find("balance > 20 and blance < 30").fields("id", "name").execute();
    for(const auto& t : doc)
        std::cout << t["id"] << " " << t["name"] << std::endl;
    
}
// 处理关系型数据库
void linkTableSql(Session_t& session)
{
    Schema schema = session->getSchema("user_db");
    Table tb = schema.getTable("account");
    // 查询表
    RowResult row_result = tb.select("id", "name", "balance")
                            .where("balance > :left and balance < :right")
                            .bind("left", 19)
                            .bind("right", 30)
                            .execute();

    for(const auto& row : row_result)
        std::cout << row[0] << " " << row[1] << " " << row[2] << std::endl;
    

    // tb.insert("id", "name", "balance").values("3", "hehehe", 10);

    // tb.update().set("name","hello").where("id=1").execute();

    
}

void testSQLCommand(Session_t& session)
{
    Schema schema = session->getSchema("user_db");
    Table tb = schema.getTable("account");

}
auto main() -> int
{
    Session_t session = createSession("localhost", "hrj", "hrj756357", "user_db");
    try {
        // NoSQLField(session);
        linkTableSql(session);
    } catch (const mysqlx::Error &e) {
        std::cerr << "MySQL X Error [" << e.what() << "]: " << e.what() << std::endl;
    
    } catch (const std::exception &e) {
        std::cerr << "Standard error: " << e.what() << std::endl;
    
    } catch (...) {
        std::cerr << "Unknown error occurred" << std::endl;
    }
    return 0;
}