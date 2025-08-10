# **MySQL的复合查询**

## SQL中各个部分的执行顺序

**标准SQL逻辑执行顺序**

- FROM（包括JOIN） - 确定数据来源

- WHERE - 行级过滤

- GROUP BY - 分组

- HAVING - 组级过滤

- SELECT - 选择列（包括计算列和聚合函数）

- DISTINCT - 去重

- ORDER BY - 排序

- LIMIT/OFFSET - 分页

## **子查询**

> SQL支持我们在SQL语句中进行子查询, 比如下面的查询

```sql
select course_id from Info where score<=>(select max(score) from Info);
```

## **多表查询**

比如常见的外键的关联

```sql

select * from table1, table2 ... # table构成的`笛卡尔积`

where table1. # 通过.进行作用域访问, 和C/C++类似

```

## **自连接** 

同一张表进行笛卡尔积, 但是很多时候我们可以通过子查询进行替换相同的效果。

```sql
select * from table_name as t1, table_name as t2;


```

## **子查询**

> 也叫做嵌套查询

## 单行子查询

> 子查询出来只有一行

## 多行子查询

> 子查询出来有多行, 这里要使用`in`关键字

多行子查询的关键字:

- in

- any

- all

- SQL支持通过()构成集合

**注意每个表都必须要有名字**