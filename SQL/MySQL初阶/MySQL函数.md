# MySQL函数

## 日期函数

- current_date() : 当时的日期

- current_time() : 当时的时间

- current_timestamp : 当时的时间戳

- date(datetime) : 返回datatime参数的日期部分(截取日期)

    ```sql
    select date('1949-10-01 00:00:00');

    ```
    - date_add(now(), interval num (day/minute/hour/second))
- now() : 当前的时间

## 字符串函数

- charset(str) : 返回字符串的字符集(编码格式)

- concat(str,...) : 拼接字符串(内置了to_string的功能)

- instr("abc1234abc", 1234) : 查询相同部分

- ucase(str) : 转成大写

- lcase(str) : 转成小写

- left(string,lenth) : 从左开始去除lenth个字符(类似substr)

- right(string, lenth) : 和left同理

- lenth(str) : 字符长度

- replace(str,search_str,replace_str) : 在str中将search_str替换成replace_str

- strcmp(string1,string2)

- substr(str, position, [,length])

- ltrim, rtrim : 从左或者从右剔除空格

