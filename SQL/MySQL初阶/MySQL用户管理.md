# MySQL的用户管理

## MySQL的账号管理(通过表进行管理)

默认用户信息维护在mysql.user这张表里面

- 创建用户
    ```sql
    create user '用户名@登录主机/ip' identified by passwd
    ```

- 修改密码
    ```sql

    ```
- 对用户赋予权限

    ```sql
    grant 权限(ALL) on db.table to user@host
    ```
- 回收权限
    ```sql
    revoke 权限(insert) on db.table from user@host;
    ```