#include <iostream>

class Base
{
public:
    virtual void print();
    virtual void print(int a);
    virtual void print(int a, int b);
};

class Derived : public Base
{
public:
    void print();
};

class Derived2 : public Base
{
public:
    using Base::print;
};

void Base::print()
{
    std::cout << "Base::print(" << ")" << std::endl;
}

void Base::print(int a)
{
    std::cout << "Base::print(" << a << ")" << std::endl;
}

void Base::print(int a, int b)
{
    std::cout << "Base::print(" << a << ", " << b << ")" << std::endl;
}

void Derived::print()
{
    std::cout << "Derived::print(" << ")" << std::endl;
}

int main(void)
{
    Base b, *pb;
    Derived d;
    Derived2 d2;

    b.print();
    b.print(1);
    b.print(2);

    d.print();
    // d.print(9)    // error, no matching function
    // d.print(99);    // error, no matching function

    d2.print();
    d2.print(123);
    d2.print(456);

    pb = &d;
    pb->print();
    pb->print(111);
    pb->print(222);

    pb = &d2;
    pb->print();
    pb->print(1010);
    pb->print(2020);

    return 0;
}
