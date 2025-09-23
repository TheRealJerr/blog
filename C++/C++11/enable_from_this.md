# C++里面enable_from_this的使用介绍

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/cbc603bf77034c8c93d2868b8a101003.png#pic_center)
![请添加图片描述](https://i-blog.csdnimg.cn/direct/adc7df13751a4f6188bd2f98dbfbe15f.gif)

在C++进行设计的时候, 我们有些时候希望将this指针暴漏给外部进行使用, 特别是在进行异步编程的时候, 我们希望外部获得该对象的使用的权利
方法当然有很多, 最简单的方式就是直接将this指针传递给外部, 但是这显然是不安全的, 我们在外部通过this指针无法很好的感知到对象的生命周期, 在异步调用的场景中, 很多时候
我们希望外界能够得到当前对象的访问接口, 简单的想法, 直接通过智能指针进行生命周期的管理, 下面是一个错误的例子。

```cpp
#include <iostream>
#include <memory>
class Object
{
public:
    
    std::shared_ptr<Object> getSharedObject()
    {
        return std::shared_ptr<Object>(this);
    }
private:
};

auto main() -> int
{
    std::shared_ptr<Object> obj = std::make_shared<Object>();
    auto obj_bak = obj->getSharedObject();

    std::cout << obj.use_count() << std::endl;
    std::cout << obj_bak.use_count() << std::endl;
    
    return 0;
}
```

![alt text](image.png)

通过结果我们发现, 这种写法显然是错误的, 该对象命名有两个shared_ptr对象指向同一块区域, 为什么`count=1`, 答案是智能指针的引用计数是通过拷贝构造函数进行`count++`,
我们直接通过`this`创建智能指针对象, 显然无法和原来对象本来进行关联。

**正确的解决方式**

```cpp
#include <iostream>
#include <memory>
class Object : public std::enable_shared_from_this<Object>
{
public:

    std::shared_ptr<Object> getSharedObj()
    {
        return shared_from_this();
    }
};

auto main() -> int
{
    std::shared_ptr<Object> obj = std::make_shared<Object>();
    auto obj_bak = obj->getSharedObj();

    std::cout << obj.use_count() << std::endl;
    std::cout << obj_bak.use_count() << std::endl;
    
    return 0;
}
```
![alt text](image-1.png)