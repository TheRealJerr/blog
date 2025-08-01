# MySQL的数据类型

### 数值类类型

|类型|字节|
|---|---|
|TINYINT|1|
|SMALLINT|2|
|MEDIUMINT|3|
|INT|4|
|BIGINT|8|

如果我们在类型后面加上unsigned, 就表示无符号整数类型。

**MySQL不需保证数据的完整性,因此不能接受数据的截断(靠扩数据越界，等等), 这同时保证了，只要插入成功, 那么数据一定成功插入了**


### bit类型

bit(M), M表示字的个数, 范围[1,64]。 

我们可以通过一个bit表示状态, 或者通过多个bit来表示位图。

### float类型

> float[(m,d)] [unsigned]
> m表示整个长度, d表示小数部分的长度
> 比如m = 2, d = 2表示从[-99.99,99.99]

### decimal

float和decimal之间存在精度之间的不同, float会自作聪明进行精度变化(比如四舍五入), decimal就不会, 相比来说, decimal的精度高于float

### 字符串类型

**MySQL这里是以字符为基本单位, 区别于C++通过字节为基本单位**

1. char(L), 固定长度字符串, L表示最大的字符的长度, 最大长度为255**字符**。

2. varchar(L), 变长字符串, 最大的长度为65535**字节**, 为什么需要限定长度, 因为MySQL的底层通过两个字节来记录变长字符串的长度。

#### varchar和char的区别

varchar和char的区别类似于静态数组和动态数组的区别, 也就是`C++`中的`std::Array`和`std::vector`的区别。

- 如果数据长度是固定的，就采用char

- 如果数据长度变化比较大, 就采用varchar


### 日期和时间类型

- data : 日期 'yyyy-mm-dd', 占用三个字节

- datetime : 时间日期格式 'yyyy-mm-dd HH:ii:ss', 占用八个字节

- timestamp : 时间戳, 占用四个字节, timestamp会自动更新

### 枚举类型(`enum`和`set`)

- 对于枚举的类型，我们可以通过下标访问枚举的值

- 优点是我们可以对于同一个选项插入多个set字段

    >
    >如果我们想要通过下标插入, 我们应该理解为比如有五个字段, 那么就有一个五个位的位图, 我们设置的数字MySql会将这个数字转成二进制理解成为位图, 然后判断你想插入的字段, 当设置的数字为0 == 0x00...会插入""即空串(在MySQL中''和NULL是不同的)。
    >


```sql

insert into test_set values ("hrj", 1, "羽毛球,代码");
Query OK, 1 row affected (0.01 sec)

mysql> select * from test_set;
+------+------+------------------+
| name | id   | hobby            |
+------+------+------------------+
| hrj  |    1 | 代码,羽毛球      |
+------+------+------------------+
1 row in set (0.00 sec)

``` 

#### 如何查找含有对应字段的表项

1. 只有某一项(严格匹配)
    ```sql
    select * from table_name where key='查找的字段'
    ```
2. 查找含有某一项(非严格匹配)

    ```sql
    select * from test_set where find_in_set("羽毛球",hobby) or find_in_set("代码",hobby);
    ```