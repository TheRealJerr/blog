# Go语法基础

## 1. 变量的声明

对于Go语言来说, 我们使用:=来进行声明和初始化, 不能重复声明，当然我们也可以使用var type来进行声明

```go
var a int = 10
// 或者
a := 10 // 通过编译器自动初始化
```

## Go语言的数组和切片

- make函数可以帮助我们自定义数组的大小类似C++ vector的size和capacity

- 由于定义好了数组不能改变, 我们只能通过append函数进行改变切片的大小, 或者使用copy函数进行复制


```go
package main

import "fmt"

func main() {
	arr := make([]int, 3, 5)
	fmt.Println(arr)
	arr = append(arr, 1)
	fmt.Println(arr)
}

```
## Go语言的map

- map是一种无序的键值对的集合, 我们可以通过key来获取value, 或者通过value来获取key


- operator[]直接访问元素

- delete函数可以删除某个key对应的value

- 那么我们如何判断某个元素是否存在于map中

如果我们能够知道Map大概得容量, 可以使用make函数来初始化map的时候指定容量

- 并发安全: map是线程不安全的, 我们可以使用sync.Mutex来保证线程的安全

- map的零值是nil

**注意的事项**

1. 如果我们只是通过类似`var prices map[string]int`来声明了这个map, 我们还需要通过make函数进行初始化才能使用, 否则会报错

2. go语言1.22版本之前的迭代器存在一些可能的陷阱
	```go
	prices := []int{10, 20, 30}

	location = make([]*int, len(prices))

	for _, price := range prices {
		location[i] = &price
		i++
	}
	```

	老版本的Go语言中for range中只存在一份, 所有的location[i]中存储的都是price的引用, 最后location中存储的都是最后一个元素的地址, 导致最后的结果可能不是我们想要的. 所以在1.22版本之后, 我们需要使用copy函数来进行复制, 或者使用make函数来初始化切片的大小.

## Go语言的指针

Go是谷歌开发的, 谷歌作为一个C++的粉丝, 所以很多特性都借鉴了C++的一些特性, 其中指针是其中一个重要的特性.

指针在未初始化的时候就是nil, 初始化之后可以通过&操作符获取指针地址, 也可以通过*操作符获取指针指向的值.

我们也可以通过new直接对内存进行分配, 并返回指针, 但是需要注意的是, 我们需要通过make函数来初始化切片, 或者使用make函数来初始化map, 否则会报错.

## Go语言的函数

- Go语言函数和C++ Java的区别就是返回值可以多个

- Go语言中函数的传递都是值传递, 而不是引用传递(区别于C++), 使用值传递, 内部函数的变化, 就不会改变外部变量的值

- Go语言对于函数的利用也很灵活, 也就是支持匿名函数, 也就是lambda表达式


## Go语言变量声明周期的讨论

Go语言变量的开辟在栈空间还是堆空间是由编译器决定的，编译器会根据该变量是否出现逃逸的现象针对变量的开辟位置进行优化，比如我在函数内部创建一个局部变量, 但是函数返回该变量的指针，编译器就会认为这个变量发生了逃逸，因此会在堆上开辟空间，而不会在栈上开辟空间。同样的函数的闭包的参数引用可能延长这个变量的生命周期,区别于C++的声明周期的基于RAII智能指针的管理, Go的gc机制会自动回收不再使用的变量, 所以不需要手动管理内存.


```go
package main

import "fmt"

func getNumber() func() int {
	i := 0
	return func() int {
		i += 1
		return i
	}
}

func main() {
	/* nextNumber 为一个函数，函数中 i 为 0 */
	nextNumber := getNumber()

	/* 调用 nextNumber 函数，i 变量自增 1 并返回 */
	fmt.Println(nextNumber())
	fmt.Println(nextNumber())
	fmt.Println(nextNumber())

	/* 创建新的函数 nextNumber1，并查看结果 */
	nextNumber1 := getNumber()
	fmt.Println(nextNumber1())
	fmt.Println(nextNumber1())
}

```
## Go语言方法

Go语言的方法和C++的类方法类似, 但是Go语言的方法可以直接访问实例变量, 而C++的类方法只能通过指针或引用来访问实例变量.

```go
func (变量 类型) 方法名(参数列表)(返回值列表){
    
}
```

Go语言的方法相比于C++的成员方法, 灵活度更高, 我们可以直接访问实例变量, 并且可以有多个返回值.

- 如果是修改对象本身, 我们就使用*type, 反之使用type, 就和C++ const修饰的成员函数和非const修饰的成员函数的思想类似

### 继承

go没有类的概念, 因此不存在继承的概念, 但是可以通过组合的方式来实现继承, 组合的方式就是将多个结构体组合成一个新的结构体, 这样就可以实现继承的效果.

```go
type People struct {
    Name string
    Age int
}

type Student struct {
    ID int
    Score int
    People    // 将People作为Student的一个属性，注意不要加类型，这就是隐式继承
}
```

## Go语言的接口

Go语言中的接口很简单，我们定义一写规则，如果某个类型实现了某个接口的所有方法，那么这个类型就实现了这个接口。其实Go语言接口类似C++的纯虚函数和多态。

```go
package main

import "fmt"

type Phone interface {
	Call()
	SendMessage()
}

type Apple struct {
	PhoneName string
}

func (a Apple) Call() {
	fmt.Printf("%s有打电话功能\n", a.PhoneName)
}

func (a Apple) SendMessage() {
	fmt.Printf("%s有发短信功能\n", a.PhoneName)
}

type HuaWei struct {
	PhoneName string
}

func (h HuaWei) Call() {
	fmt.Printf("%s有打电话功能\n", h.PhoneName)
}

func (h HuaWei) SendMessage() {
	fmt.Printf("%s有发短信功能\n", h.PhoneName)
}

func main() {
	a := Apple{"apple"}
	b := HuaWei{"huawei"}
	a.Call()
	a.SendMessage()
	b.Call()
	b.SendMessage()

	var phone Phone                    // 声明一个接口类型phone
	phone = new(Apple)                 // 注意这种创建方式，new函数参数是接口的实现
	phone.(*Apple).PhoneName = "Apple" // 这里使用断言给phone的成员赋值，后面会讲到接口的断言
	phone.Call()
	phone.SendMessage()
}
```

所有的类型都实现了空接口, 也就是空接口可以存储任意类型的值

```go
func Println(a ...interface{}) (n int, err error)
func Print(a ...interface{}) (n int, err error)
```

### 类型断言

首先我们需要明确, 我们可以将任意类型复制给空接口, 但是不能将空接口复制给其他类型, 因此我们需要使用类型断言来判断某个接口是否实现了某个接口的所有方法.

```go
value, ok := x.(T)
```