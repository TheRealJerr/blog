# C++11
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/8352dc4837f448b1970c026f73d30096.png)

## 引言
C++组委会10年磨一剑吧，制定了新的一套C++语法，可以说，C++11对于C++来说，是一场革命性的变化，基于C++之后的变成语言，采用了他们的长处，设计除了一套比较好的新的语法特性，有些语法略显鸡肋，但是有些语法，确实感觉让C++这门语言都焕然一新的感觉，这篇文章就是带领大家了解一下C++11提出的lambda表达式和包装器的的一些使用方式和细节。

## lambda表达式

学过python的朋友们应该都知道，lambda表达式最早应该是python在提出，他的主要思想我认为是方便程序员通过面向对象的方式来管理函数。也就是说，我们希望将函数可看做一个对象，而不再基于C语言中的函数指针的视角来看待函数。

- C语言习惯将函数看成一个指针
	```c
	int plus(int left,int right) { return left + right; }
	int(*p)(int,int) = &plus;
	```
- 而C++作为一个面向对象的语言，更期望与将函数看做一个对象。

所以lambda表达式就是一个对象。
首先我们先了解lamda表示的使用方式和注意事项。
```cpp
auto plus = [](int left,int right)->int { return left + right; };
plus(1, 2);
```
- `[]`: 方括号中表示我们需要捕获的内容，具体什么意思呢
	- 1. 如果我们前面有一个值`int a  = 0`, 那么如果我们在`[]`加上`a`就是通过拷贝的方式捕获了a，可以在后面`{}`的作用域中使用，如果使用`&a`就是创建一个a = 外部a的引用
	- 2. 特别如果是=，表示拷贝捕获当前栈区的所有值。如果&，表示捕获成引用
- `()` : 表示这个函数对象的参数
- `->`： 表示返回值的类型，但是我们不写它能够推断，通过return

实例
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/1b2514958a944558afb61b95c4db9dcd.png)

==**好处**==：
我们在定义访问函数的时候能够更加的自由和灵活。

如果到这里你认为lamda表达式没什么用，请继续看。
## 仿函数
> 我们知道operator可以重载运算符，那么为什么不能operator()，这样不就是函数吗

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/76d20b42825a408b96594491ba5a2b08.png)
## 小结

对吧，现在我们有三种表示函数的方式，仿函数 + 普通函数 + lambda函数，你不觉得lambda表达式就是匿名的仿函数吗，或者我告诉你，lambda表达式就是基于仿函数来进行设计的，并且你捕获的值就是作为这个匿名对象的成员变量，是不是有点感觉了。

## 包装器
> 现在我们有三种表示函数的方式，我们可不可以通过一种类型可以统一这三种表达方式，有的有的，有的兄弟，这种就是我们现在要讲的包装器

![](https://i-blog.csdnimg.cn/direct/89497d3b7caa4323852c51e840406fac.png)
我们通过包装器将这三种类型组织起来了，这不就是大一统了嘛，我们可以通过`function`来灵活管理各种函数描述类型，任何都是对象。

## 有什么用 ？
将函数作为成员变量

我们讲类的时候知道成员函数，但是我们现在可以将一个函数作为成员变量，这有什么用？

-  回调函数
	回调函数就是典型的就是将函数作为参数的类型，不用像C语言那么恶心的表示函数指针的方式，直接通过包装器直接解决。

比如我说一个应用场景，我想要实现一个计算器，我们有很多操作的方式，比如`+ - * / sin cos tan ...`, 最简单的思想就是`if else `或者`switch case`， 但是操作多了感觉就是不优雅，那么我们有什么优雅的替代吗？

```cpp
using operation_t = std::function<double(double,double)>;
std::unordered_map<std::string, operation_t> operation_tool;
operation_tool["plus"] = [](int left,int right) ->int { return left + right; };
operation_tool["plus"](1 , 2);
```
是不是优雅多了。

## 参数绑定, std::bind

> std::bind 是 C++11 引入的一个函数适配器，用于 部分应用（Partial Application） 或 绑定参数，它可以：
固定（绑定）函数的某些参数，生成一个新的可调用对象。调整参数顺序，改变函数参数的传递方式。与 std::placeholders 结合，灵活地控制参数的传递。

### 基本用法
- 1. 绑定普通函数
	```cpp
	#include <functional>
	#include <iostream>
	
	void print_sum(int a, int b) {
	    std::cout << a + b << std::endl;
	}
	
	int main() {
	    // 绑定 print_sum 的第一个参数为 10，第二个参数由调用时提供
	    auto bind_print = std::bind(print_sum, 10, std::placeholders::_1);
	    bind_print(20);  // 输出 30（10 + 20）
	}
	std::placeholders::_1 表示调用 bind_print 时传入的第一个参数。
	```
- 2. 绑定成员函数
成员函数需要额外绑定对象（指针或引用）：
	```cpp
	#include <functional>
	#include <iostream>
	
	class Math {
	public:
	    void print_sum(int a, int b) {
	        std::cout << a + b << std::endl;
	    }
	};`
- 3. 调整参数顺序
std::bind 可以改变参数的顺序：
	```cpp
	void print_values(int a, int b, int c) {
	    std::cout << a << ", " << b << ", " << c << std::endl;
	}

	int main() {
	    // 调整参数顺序：原函数是 (a, b, c)，现在改为 (c, b, a)
	    auto bind_reorder = std::bind(print_values, std::placeholders::_3, std::placeholders::_2, std::placeholders::_1);
	    bind_reorder(1, 2, 3);  // 输出 "3, 2, 1"
	}
	```
_1 对应调用时的第一个参数，_2 对应第二个，依此类推。

- 4. 绑定部分参数
可以只绑定部分参数，剩下的由调用时提供：

	```cpp
	void print3(int a, int b, int c) {
	    std::cout << a << ", " << b << ", " << c << std::endl;
	}
	
	int main() {
	    // 只绑定第一个参数，剩下两个由调用时提供
	    auto bind_partial = std::bind(print3, 100, std::placeholders::_1, std::placeholders::_2);
	    bind_partial(200, 300);  // 输出 "100, 200, 300"
	}**
	```
## std::bind的坑
`std::bind`一般一定绑定的是值而不是引用，什么意思。
```cpp
int plus(int& left,int& right) { return left + right; }
int a = 0,b = 1;
auto t = std::bind(&plus, a, b);
```
看上面的代码，看似a, b是作为引用bind， **实际上他是传值后，然后传递创建好的新数据作为引用**，对于深度数据，很有可能出现的就是深拷贝的拷贝开销问题，那么怎么解决。
- 1. `std::ref` 指定传递引用
```cpp
auto t = std::bind(&plus, std::ref(a), std::ref(b));
```
- 2. lambda表达式解决
```cpp
auto t = [&a, &b]() -> void { return plus(a + b); }
```

## 总结
现在看完的你还不能完全体会这几个新特性的作用，在未来开发中你一定有一天会想到今天我说的这些，觉得豁然开朗，如果我的文章对你有帮助，那真的泰裤辣。