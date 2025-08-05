# MySQL函数

## 日期函数

- current_date() : 当时的日期

- current_time() : 当时的时间

- current_timestamp : 当时的时间戳

- date(datetime) : 返回datatime参数的日期部分(截取日期)

    ```sql
    select date('1949-10-01 00:00:00');

    ```

- now() : 