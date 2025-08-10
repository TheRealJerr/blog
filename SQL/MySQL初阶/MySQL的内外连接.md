# MySQL的内外连接


## MySQL的内连接

> 笛卡尔积本质就是内连接的一种

```sql
select 字段 from 表1 inner join 表2 on 连接条件 and 其他条件
 select stu_grade.id, stu_grade.name,classMap.class_name from stu_grade inner join classMa
p on stu_grade.class_
+----+------+------------+
| id | name | class_name |
+----+------+------------+
|  0 | hrj  | 1班        |
+----+------+------------+
1 row in set (0.00 sec)
```

## MySQL的外连接

左外连接和右外连接

> 我们左右表中的某一项并非一定能够完全能够映射, 左外连接就是保证做链接的所有项