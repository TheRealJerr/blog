# Redis的常用命令

## Redis键

[command key_name]

- del : 删除键

- dump key : 序列化key

- exists : 是否存在

- expire key seconds : 设置过期时间, 秒为单位

- pexpire key : 毫秒为单位

- keys : 正则化查找

- move key db : 移动数据

- persist key : 