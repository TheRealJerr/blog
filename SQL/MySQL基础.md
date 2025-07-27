# MySQL初阶

## 登录mysql

> mysql -u root -p "后面跟你的passwd"

## MySQL数据库基础

### 重启服务

```shell
systemctl restart mysqld
``` 

### 登录选项

- -u : 用户选项(-u root就是以root用户登录)

- -h : ip地址(没有就是本机环回) 

- -P : 指明端口号

- -p : passwd(对应用户的密码)

### 数据库基础

> MySQL是一个网络服务, 默认是3306
> mysqld是服务端, mysql是客户端
> mysql是一套给我们提供数据存取服务的网络程序

**数据库**

> 在磁盘(MySQL)或者内存(Redis)中进行存储的特定结构组织的数据




