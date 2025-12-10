#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>

class Base
{
public:
    virtual void printNumber(int number = 3) const
    {
        std::cout << "Base::printNumber(" << number << ")" << std::endl;
    }
private:

};

class Derived : public Base
{
public:
    void printNumber(int number = 4) const override
    {
        std::cout << "Derived::printNumber(" << number << ")" << std::endl;
    }
};

void test()
{
    const Base& b = Derived();
    b.printNumber();
}

int main()
{
    test();
    return 0;
}