# MySQL的基本查询

---

## 表的增删查改

### insert(插入)

```sql
insert [info] table_name [(colume, [,colume] ...)] values (value_list) ...
```

对于value_list我们通过`,`作为分隔符

#### 插入替换

类似于`create`里面的`if not exists`, 我们使用`on duplint key`