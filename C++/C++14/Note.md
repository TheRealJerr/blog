# constexpr关键字

constexpr是C++11引入的关键字，用于声明常量表达式。常量表达式是指在编译时可以确定结果的表达式。constexpr函数的返回值可以作为常量表达式使用，这意味着可以在编译时计算函数的值，而不是在运行时。

**常量表达式**
> 常量表达式是指在编译时可以确定结果的表达式。常量表达式可以出现在任何地方，包括函数参数、函数返回值、成员函数的返回值、数组大小、switch语句的表达式、模板参数等。


constexpr函数的声明必须满足以下条件：

1. 函数体内只能包含常量表达式。
2. 函数不能修改任何外部变量的值。
3. 函数不能调用其他非constexpr函数。

constexpr函数的返回值必须是一个常量表达式，这意味着它必须是一个字面值、常量表达式、引用、指针、成员函数的结果或成员变量的引用。

constexpr函数的调用可以在编译时进行，因此可以提高程序的运行效率。

constexpr函数的声明和定义都必须使用constexpr关键字。

```c++
constexpr int add(int a, int b) {
    return a + b;
}

int main() {
    constexpr int x = add(1, 2);
    return 0;        
}   
```


## auto关键字

auto关键字可以帮助我们自动推导类型

1. auto对于普通类型
    ```c++
    auto x = 10;
    auto y = "hello";
    ```

2. auto对于引用类型
    ```c++
    int a = 10;
    auto& b = a;
    ```

3. auto对于指针类型
    > auto不会保留顶层const, 但是会保留底层const
    ```c++
    int* p = nullptr;
    auto c = p;
    ```

4. auto对于函数返回值类型
    ```c++
    auto f() {
        return 10;
    }
    ```

5. auto&可以匹配左值，auto&&可以匹配右值
    ```c++
    int a = 10;
    auto& b = a; // 左值
    auto&& c = 10; // 右值
    ```

## decltype关键字

**decltype会保留对象类型的const和引用区别于auto**

decltype关键字可以帮助我们获得表达式的类型。decltype(expression)返回expression的类型。decltype(auto)是decltype的一种简化形式。decltype(auto)可以自动推导表达式的类型，并将其绑定到一个变量上。


```c++
int a = 10;
decltype(a) b = a;
```

**注意**:

decltype(*p)推导出来的是引用, 包括operator[]推导出来的也是引用