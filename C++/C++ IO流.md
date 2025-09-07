# C++ IO流
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/cbc603bf77034c8c93d2868b8a101003.png#pic_center)
![请添加图片描述](https://i-blog.csdnimg.cn/direct/adc7df13751a4f6188bd2f98dbfbe15f.gif)

## 引言
谈到IO流，有些读者可能脑海中第一个想到的C++程序员的最基础的std::cout ， std::cin两个类的使用，对的，这个就是一个典型的IO流，所以逆天我们这篇文章会基于C++ IO流的原理和各种应用场景进行深入的解读。
## C语言的数据输出
C语言我们如果进行IO, 我们使用的的scanf和prinf， 或者说我们实际上是通过`FILE*` 进行IO , 因为了解底层的朋友们应该也知道 ，`scanf`其实是针对`stdin`，`printf`针对`stdout`的封装。

C语言借助缓冲区实现用户层和设备之间进行IO。
***缓冲区的作用***
- 1. 可以帮助我们屏蔽底层的差异，因为各种操作系统组织数据的方式不同，我们通过缓冲区抹平这种差异。
- 2. 使用缓冲区可以实现行读取的操作，因为操作系统没有行的概念，我们可以在缓冲区指定语言级别的规则。

## 什么是流
> “流”即是流动的意思，是物质从一处向另一处流动的过程，是对一种有序连续且具有方向性的数
据（ 其单位可以是bit,byte,packet ）的抽象描述。
C++流是指信息从外部输入设备（如键盘）向计算机内部（如内存）输入和从内存向外部输出设
备（显示器）输出的过程。这种输入输出的过程被形象的比喻为“流”。

包括TCP协议，其实也是一种流式传输的模型，当然这是后话。

## C++流的设计
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/bdbef9f9028a4a29873415c718b2a69b.png)

### 标准IO流
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/c3ae1491dccd45b5919b8ad2e35910e8.png)


C++ 标准提供了全局的流对象，`std::cin， std::cout ， std::cerr， std::clog`，当然如果理解C语言的读者，当然发现这里就是映射到我们的`stdin, stdout, stderr` ， 如果熟悉操作系统的就会发现就是映射到对应的0, 1, 2 的文件描述符。

注意事项：
- 1. 标准流针对标准中内置类型都进行了重载，int , double , 包括std::string。
- 2. 输入类型的类型必须和提取的类型一致，不然就会出错，但是我们可以通过修改流的状态来继续进行。
- 3. 流重载的状态判断
	```cpp
	// type
	istream& operator(istream&,type) {}
	explicit operator bool() const {} // 
	```
- 4. 支持重定义自定义类型
	```cpp
	class Data
	{
	public:
		friend istream& operator<<(istream& in, Data& d);
	private:
		int data_;
	};
	
	istream& operator<<(istream& in, Data& d)
	{
		in >> d.data_;
		return in;
	}
	```
### C++的文件IO流 (fstream)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/8c2d901cc7724bcc8170cb21b6e94ef3.png)

C++ 根据文件分为`文本文件`和`二进制文件`，采用文件流操作文件：
- ifstream : 读取文件
- ofstream : 写入文件
- fstream : 读写文件

==**那么C++的文件流有什么优势吗？**==
支持重载就是C++文件流最大的优势，从上面的图中我们可以看到fstream 继承了 iostream ， 所有我们可以通过重载iostream的`>>` 和`<<` 来进行重载自定义类型
```cpp
class Data
{
public:
	friend istream& operator<<(istream& in, Data& d);
private:
	int data_;
};

istream& operator<<(istream& in, Data& d)
{
	in >> d.data_;
	return in;
}
int main()
{
	std::ifstream ifs(filename, std::ios_base::in);
	Data d;
	ifs << d;
	return 0;
}
```
### stringstream
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/89a99621bbb74e6a934842f33d3fecde.png)

你以为这样就完了吗，当然没有，还以一种流，字符流(`stringstream`)，他的作用是什么呢？我们不妨使用`Linux`操作系统下`一切皆文件的思想`来理解
- **标准输入输出流**：其实本质就是我们将显示器看成一个文件，我们可以全局的std::cin, std::cout, 这就和C语言中我们可以通过fscanf(stdin, ...) 来替代scanf，其实就是标准输入输出语言层面的特殊强调。
- **文件流**：当然就是操作文件
- **字符流**： 我们将字符串也想象成一个文件，我们通过`<<`，`>>`操作字符串。
	**实例**
	```cpp
	std::string buffer = "1 2 3 4";
	std::stringstream ssm(buffer);
	int a1 , a2, a3 , a4;
	ssm << a1 << a2 << a3 << a4;
	```
同时我们还是可以重载iostream的`<<`和`>>`进行重载。 
**stringstream的优点**:
- 1. 更加灵活的操控字符串，平时我们只能通过std::to_string来将转换字符串，但是stringstream支持各种类型(重载后)。
- 2. 我们可以发现C++14后的很多类型都不能支持to_string, 比如std::chrono里面的各种类型，但是他们支持iostream ， 也就是说我们可以通过stringstream构建字符串。

## 总结
通过这篇文章，我们提出了C++的一套IO体系，作为一个C++程序员，我们也不能老是只会使用C风格的接口，我们也需要学习C++自己的一套体系，并且C++的IO设计也比C更加灵活，让程序员能够更加灵活的操作IO。

