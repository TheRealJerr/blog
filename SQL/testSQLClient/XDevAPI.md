好的，我来为你总结 MySQL X DevAPI 的常见用法并提供相关资源。

## 📚 官方文档路径

**主要文档首页：**
- [MySQL Connector/C++ 8.0 Developer Guide](https://dev.mysql.com/doc/connector-cpp/8.0/en/)
- [X DevAPI Reference](https://dev.mysql.com/doc/connector-cpp/8.0/en/connector-cpp-appendix-devapi.html)

**重要章节：**
- [X DevAPI Usage Examples](https://dev.mysql.com/doc/connector-cpp/8.0/en/connector-cpp-examples.html)
- [X DevAPI Reference](https://dev.mysql.com/doc/dev/connector-cpp/8.0/devapi_ref.html)

## 🚀 X DevAPI 常见用法总结

### 1. 基本头文件包含

```cpp
#include <mysqlx/xdevapi.h>
using namespace mysqlx;
```

### 2. 建立连接

```cpp
// 方式1：直接连接
Session sess("localhost", 33060, "username", "password", "database");

// 方式2：使用 SessionSettings（推荐）
SessionSettings settings(
    SessionOption::HOST, "localhost",
    SessionOption::PORT, 33060,
    SessionOption::USER, "username",
    SessionOption::PWD, "password",
    SessionOption::DB, "database",
    SessionOption::SSL_MODE, SSLMode::DISABLED
);
Session sess(settings);

// 方式3：连接字符串
Session sess("mysqlx://username:password@localhost:33060/database");
```

### 3. 文档存储操作（NoSQL 风格）

```cpp
// 获取集合（类似表）
Schema schema = sess.getSchema("test_db");
Collection users = schema.getCollection("users");

// 插入文档
users.add(R"({
    "name": "John Doe", 
    "age": 30, 
    "email": "john@example.com",
    "address": {
        "city": "New York",
        "zipcode": "10001"
    }
})").execute();

// 批量插入
users.add(
    R"({"name": "Alice", "age": 25})",
    R"({"name": "Bob", "age": 35})"
).execute();

// 查询文档
DocResult docs = users.find("age > 25")
                    .fields("name", "age", "address.city")
                    .sort("age DESC")
                    .limit(10)
                    .execute();

for (DocResult::Iterator it = docs.begin(); it != docs.end(); ++it) {
    std::cout << "Document: " << *it << std::endl;
    std::cout << "Name: " << (*it)["name"] << std::endl;
}

// 更新文档
users.modify("age > 30")
     .set("status", "senior")
     .execute();

// 删除文档
users.remove("age < 18").execute();
```

### 4. 关系型数据操作（SQL 风格）

```cpp
// 执行 SQL 查询
SqlResult result = sess.sql("SELECT * FROM users WHERE age > ?")
                     .bind(25)
                     .execute();

// 处理结果集
for (Row row : result) {
    std::cout << "ID: " << row[0] 
              << ", Name: " << row[1] 
              << ", Age: " << row[2] << std::endl;
}

// 执行 DML 操作
sess.sql("INSERT INTO users (name, age) VALUES (?, ?)")
    .bind("Charlie", 28)
    .execute();

// 事务处理
sess.startTransaction();
try {
    sess.sql("UPDATE accounts SET balance = balance - 100 WHERE id = 1").execute();
    sess.sql("UPDATE accounts SET balance = balance + 100 WHERE id = 2").execute();
    sess.commit();
} catch (...) {
    sess.rollback();
    throw;
}
```

### 5. 表操作（关系型）

```cpp
// 获取表
Table users = schema.getTable("users");

// 查询表
RowResult rows = users.select("id", "name", "age")
                     .where("age > :age_param")
                     .bind("age_param", 25)
                     .orderBy("name ASC")
                     .execute();

for (Row row : rows) {
    std::cout << "ID: " << row[0] 
              << ", Name: " << row[1] 
              << ", Age: " << row[2] << std::endl;
}

// 插入数据
users.insert("name", "age")
     .values("David", 32)
     .values("Eva", 29)
     .execute();

// 更新数据
users.update()
     .set("age", 40)
     .where("name = :name")
     .bind("name", "David")
     .execute();

// 删除数据
users.remove()
     .where("age > :max_age")
     .bind("max_age", 100)
     .execute();
```

### 6. 预处理语句和参数绑定

```cpp
// SQL 预处理语句
SqlStatement stmt = sess.sql("INSERT INTO users (name, age, email) VALUES (?, ?, ?)");
stmt.bind("John", 30, "john@example.com").execute();
stmt.bind("Jane", 25, "jane@example.com").execute();

// 文档查询参数绑定
DocResult docs = users.find("age > :min_age AND name LIKE :name_pattern")
                    .bind("min_age", 25)
                    .bind("name_pattern", "J%")
                    .execute();
```

### 7. 错误处理

```cpp
try {
    Session sess("localhost", 33060, "user", "pass");
    // 各种操作...
    
} catch (const mysqlx::Error &e) {
    std::cerr << "MySQL X Error [" << e.code() << "]: " << e.what() << std::endl;
    
} catch (const std::exception &e) {
    std::cerr << "Standard error: " << e.what() << std::endl;
    
} catch (...) {
    std::cerr << "Unknown error occurred" << std::endl;
}
```

### 8. 元数据查询

```cpp
// 获取数据库列表
std::list<Schema> schemas = sess.getSchemas();
for (const Schema &schema : schemas) {
    std::cout << "Schema: " << schema.getName() << std::endl;
}

// 获取表列表
Schema db = sess.getSchema("test_db");
std::list<Table> tables = db.getTables();
for (const Table &table : tables) {
    std::cout << "Table: " << table.getName() << std::endl;
}

// 获取集合列表
std::list<Collection> collections = db.getCollections();
for (const Collection &coll : collections) {
    std::cout << "Collection: " << coll.getName() << std::endl;
}
```

## 🔧 编译命令

```bash
# 编译 X DevAPI 程序
g++ -o program program.cpp -lmysqlcppconnx

# 如果同时使用传统 API
g++ -o program program.cpp -lmysqlcppconn -lmysqlcppconnx

# 使用 pkg-config（如果可用）
g++ -o program program.cpp $(pkg-config --libs mysqlcppconn9)
```

## 📋 常用类总结

| 类名 | 用途 |
|------|------|
| `Session` | 数据库会话连接 |
| `Schema` | 数据库模式 |
| `Collection` | 文档集合 |
| `Table` | 关系表 |
| `SqlResult` | SQL 查询结果 |
| `DocResult` | 文档查询结果 |
| `Row` | 数据行 |
| `DbDoc` | 文档对象 |

## ⚠️ 注意事项

1. **端口号**：X DevAPI 使用 **33060** 端口
2. **MySQL 版本**：需要 MySQL 8.0+ 并启用 X 插件
3. **启用插件**：`INSTALL PLUGIN mysqlx SONAME 'mysqlx.so'`
4. **性能**：文档操作比 SQL 稍慢，但开发效率更高
5. **混合使用**：可以在同一个程序中混合使用文档和关系操作

## 🎯 选择建议

- **使用文档存储**：当数据结构灵活，需要 JSON 支持时
- **使用关系表**：当数据结构固定，需要复杂查询和事务时
- **使用 SQL**：当需要执行存储过程或复杂报表查询时

X DevAPI 提供了非常现代和灵活的编程接口，特别适合需要同时处理关系型和文档型数据的应用场景。