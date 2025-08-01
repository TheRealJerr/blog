#include <iostream>
#include <pthread.h>
#include <sys/types.h>
#include <functional>

using thread_task_t = std::function<void(void)>; 
class Thread
{
public:

    static void* handler(void* t)
    {
        Thread* tmp = static_cast<Thread*>(t);
        if(tmp->_task) tmp->_task();
        return nullptr;
    }
    Thread() = default;

    template <class Func,class ...Args>
    Thread(Func&& func,Args&&... args)
    {   
        _task = std::bind(std::forward<Func>(func), std::forward<Args>(args)...);
        ::pthread_create(&_tid, nullptr, handler, this);
    }


    void join()
    {
        pthread_join(_tid,nullptr);
    }

    void detach()
    {
        pthread_detach(_tid);
    }
private:

    thread_task_t _task;
    pthread_t _tid;
};