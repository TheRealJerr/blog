# MySQL的基本查询

---

## 表的增删查改

### insert(插入)

```sql
insert [info] table_name [(colume, [,colume] ...)] values (value_list) ...
```

对于value_list我们通过`,`作为分隔符

#### 插入替换
1. 我们使用`on duplicate key update`, 表示如果存在主键冲突, 会进行更新, 这个字段后面还有写更新的字段

2. `replace`: 和insert的方式一致

## select (查询)

1. select ... from ... where ...

2. select可以计算表达式: `select math_grade+chinese_grade from ... where ...`

3. 可以重命名select what as ...

4. distinct参数,表示可以进行数据的去重

### where字句

1. MySQL中比较应该实用`=`而不是C/C++中的`==`, 但是更推荐`<=>`

2. 不等于,`!=或者<>`

3. 区间 between l and r [l,r]

4. 在一个集合中`in (option ...)`

5. is null和is not null表示是否为空

6. like: 模糊匹配,`%`表示任意多个字符,`_`表示任意一个字符

**注意点**

- select中as的执行顺序后与where, 所以where字句不能使用as的重命名的名字.

- where字句中可以加上`()`表示一个单元,这一点和`C/C++`一致

- 空和`NULL`是不同的。

### **select进行排序**

```sql
order by [colume...]

```

1. 普通排序

```sql
order ... by  
select name from stu order by math_grade [asc | desc]

ascending表示升序, descending表示降序
```

2. 层级排序(先数学 再语文 然后英语)

```sql
select name from stu order by math_grade asc, english_grade desc
```

**注意点**

- `order by`的顺序还在别名的后面, 因此我们可以通过别名进行排序

### limit(简单的分页功能) 避免内存压力太大

limit 起始行(最开始是第一行), 步长(从开始行走的步长) 如果没有起始行，默认是起始行=1





## update(更新/修改)

```sql
update table_name set column = expr [,column=expr]
```

**将倒数前三名的成绩加5分**

```sql
update stu_grade set grade=grade+5 order by grade asc limit 3;
```



## (删除)

```sql
delete from table_name [column...]
```
**truncate可以清空auto_increment**

```sql
truncate from table_name [colume...]
```

**去重表中的数据**


## 创建一个相似的表

```sql
create table new_table_name like old_table_name;
```

## 聚合查询

- count : 统计有多少行
    ```sql
    select count(*) from table_name
    ```

- sum : 进行聚合(只能是数字)
    **求平均分**
    ```sql
    select sum(grade)/count(grade) from stu_grade;
    ```

- avg : 求出平均值(只能是数字)

- max : 数字最大值(只能是数字)mo

- min : 数字最小值(只能是数字)

## 分组(group by字句)

> 提供根据某一列进行分组的需求

group by 表示你要通过那一列进行分组

```sql
select max(sal) as 最高, avg(sal) 平均 from table_name group by 列名 
```

## having

> 对聚合的数据进行条件筛选

**having和where的区别**:

- `where`是对具体的任意列进行条件筛选

- `having`是对分组聚合之后的结果进行条件少选
