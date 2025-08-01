# MySQL中的约束

> 表中一定要有各种约束, 通过约束，我们能够未来保证数据库中的数据是合法的。
> 约束的目标就是保证数据的完整性和可预期性。

## 空属性

- 两个值 : null(默认的) 和 not null(不为空)

- 数据库的默认字段都为空, 但是实际开发, 尽量保证字段不为空。 

## 默认值约束(DEFAULT)

我们通过在类型后面设置default参数

> default值如果设置, 如果有确定的数据, 就设置数据, 没有就default。

## 谈谈空和default之间的关系。

- 如果我们没有指定一列要插入, 用的是default, 如果在建表中, 没有默认值, 就会报错。

- 在默认情况下, 我们的default是null, 当我们设置了not null, 我们就必须设置default, 不然就会报出没有对应的default值进行插入。

- default和not null不冲突而是互相补充。

- 如果我们默认设置了not null， 没有默认的default(因为默认的default就是null)

## comment(列描述)

> 针对表中的内容进行描述(类似于Java/C++中的注释)

## zerofill(根据位数补零)

> zerofill的作用就是将我们忽略的0进行填充, 比如我们int(10), 如果只是数据1并且设置了zerofill, 就会将高位设置成为0, 0000000001。



## 主键(primary key)

> 主键要么只有一个, 要么没有, 逐渐就是这张表中最重要的一项, 类似于迭代器的作用, 逐渐必须是唯一的。

```sql
create table if not exists test_key(
    id int unsigned primary key comment "学号"
);
```

**(删除主键), 不会删除这一列, 但是会删除主键约束**

```sql
alter table table_name drop primary key
```

## 复合主键, 多个元素共同唯一(同时相同才会冲突)

```sql
create table Info (
    id int unsigned comment "编号",
    course_id int unsigned comment "课程编号",
    score tinyint unsigned comment "课程成绩",
    primary key(id,course_id)
);
```

## 自增长(auto_increment)

自动增长的约束， 他能够实现自动增长，当我我们也可以手动的插入, 相当于自动的设置DEFAULT值。每次自动增长

```bash
+-------+------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| Info  | CREATE TABLE `Info` (
  `id` int unsigned NOT NULL AUTO_INCREMENT,
  `course_id` int unsigned NOT NULL COMMENT '课程编号',
  `score` tinyint unsigned DEFAULT NULL COMMENT '课程成绩',
  PRIMARY KEY (`id`,`course_id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb3         |
+-------+------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
1 row in set (0.00 sec)
```

我们可以手动设置`AUTO_INCREMET=?`来设置自增的开始

## 唯一键

```sql
create table stu(
  id char(20) unique comment "学生的的唯一键",
  name varchar(20) not null
);
```

> 唯一键可以冲突(多个项相同), 并且唯一键可以为NULL

