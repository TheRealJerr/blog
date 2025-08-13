# **MySQL索引**


## **添加索引**

```sql
alter table table_name index(liebiaoxiang)
```

## MYSQL刷新进行读写的基本单位

16kb

MYSQL通过16kb作为自己管理数据的基本单位

默认我们是根据`primary key`作为排序的依据

page很多时候相当于目录和目录对应内容之间的关系

## 为什么MySQL会默认根据`primary key进行排序`

方便引入页内目录