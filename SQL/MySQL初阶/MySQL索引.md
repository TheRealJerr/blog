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

用page管理page, 类似于多级页表

## MYSLQ  B+的数据结构

1. 叶子节点保存有数据，路径节点没有数据，这棵树一定是一个矮胖的数，这样可以减少我们访问的时间。

2. 叶子节点通过链表进行级联。(这是B+树的特点)

**这个B+数我们称作MySQL innodb下的索引结构**

### 如果没有主键呢？

MySQL会有默认主键

### MYSQL为什么选择B+树

1. 链表 : IO和搜索的效率都是不太满足的

2. 二叉树 : 二叉树是瘦高的，IO PAGE交互过深

3. 红黑 && AVL : IO PAGE交互深

4. Hash : 官方支持的索引实现方式中, MySQL是支持Hash的

5. 不选择B数, 相对于B+树的更高

## 聚簇索引和非聚簇索引

1. 对于innodb来说，默认存储主键索引，如果添加新的索引，新索引的叶子节点存储的是对应的主键映射，这种机制叫做回表查询的机制

2. 对于myisam, 就是新构建一个新索引的B+树


## 索引操作

```sql
alter table table_name index(table_line)

alter table table_name drop index table_line
```

**那些情景添加索引比较好**:

1. 很少修改

2. 经常在where字句中出现

3. 唯一性比较好

4. 比较频繁作为查询条件的索引

