// 写一个对象内存池

#include <iostream>
#include <mutex>
#include <unistd.h>

#define GET_NEXT(PTR) (*(void**)(PTR))
#define SET_NEXT(PTR, NEXT) (*(void**)(PTR) = NEXT)

template <class T>
class ObjectPool
{
    void getLargeMem()
    {
        // 获取大块内存
        large_mem_ = ::sbrk(default_pool_size);
        if(large_mem_ == nullptr) throw std::bad_alloc();
    }

    void* allocate(size_t size)
    {   
        void* ret = nullptr;
        if(pool_head_ != nullptr)
        {
            ret = pool_head_;
            pool_head_ = GET_NEXT(pool_head_);
        }

        else
        {
            // 内存链表为空, 切割内存块
            if(large_mem_ == nullptr || default_pool_size - used_ < size)
            {
                // 剩余内存不足, 申请大块内存
                getLargeMem();
                used_ = 0;
            }
            ret = large_mem_;
            large_mem_ = (char*)large_mem_ + size;
            used_ += size;
        }
        
        return ret;
    }

    void deallocate(void* ptr)
    {
        SET_NEXT(ptr, pool_head_);
        pool_head_ = ptr;

    }

public:
    
    template <class ...Args>
    auto* alloc(Args&&... args)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        void* ptr = allocate(sizeof(T));
        if(ptr == nullptr) throw std::bad_alloc();
        return new(ptr) T(std::forward<Args>(args)...);
    }

    void dealloc(void* ptr)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        T* obj = static_cast<T*>(ptr);
        obj->~T();
        deallocate(ptr);
    }

private:
    // 内存安全的开辟空间
    std::mutex mtx_;
    // 大块内存
    void* large_mem_; 
    // 大块内存已使用的大小
    size_t used_; 
    // 内存池头指针
    void* pool_head_;
    // 对齐大小
    constexpr static size_t match_size = sizeof(T) > sizeof(void*) ? sizeof(T) : sizeof(void*);
    // 默认内存池的带下
    static constexpr size_t default_pool_size = 1024 * 1024; // 1MB
};

class Date
{
public:

    Date(int month, int year,int day) : 
        month_(month), year_(year), day_(day) 
    {}

    int month() const { return month_; }
    int year() const { return year_; }
    int day() const { return day_; }
private:
    int month_;
    int year_;
    int day_;
};

void testAlloctor()
{
    try{
        ObjectPool<Date> pool;
        Date* date1 = pool.alloc(1, 2021, 1);
        std::cout << "date1: " << date1->month() << " " << date1->year() << " " << date1->day() << std::endl;

        Date* date2 = pool.alloc(2, 2022, 2);
        std::cout << "date2: " << date2->month() << " " << date2->year() << " " << date2->day() << std::endl;

        pool.dealloc(date1);
        pool.dealloc(date2);
    }catch(const std::bad_alloc& e){
        std::cerr << "bad_alloc: " << e.what() << std::endl;
        return;
    }
    
}

int main()
{
    testAlloctor(); 
    return 0;
}