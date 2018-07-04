#include <iostream>

class Base
{
public:
    virtual int fcn();
};

class Derived1 : public Base
{
public:
    int fcn(int);
    virtual void fcn2();
};

class Derived2 : public Derived1
{
public:
    int fcn(int);
    int fcn();
    void fcn2();
};

int Base::fcn()
{
    std::cout << "Base::fcn()" << std::endl;
}

int Derived1::fcn(int i)
{
    std::cout << "Derived1::fcn(" << i << ")" << std::endl;
}

void Derived1::fcn2()
{
    std::cout << "Derived1::fcn2()" << std::endl;
}

int Derived2::fcn(int i)
{
    std::cout << "Derived2::fcn(" << i << ")" << std::endl;
}

int Derived2::fcn()
{
    std::cout << "Derived2::fcn()" << std::endl;
}

void Derived2::fcn2()
{
    std::cout << "Derived2::fcn2()" << std::endl;
}

int main(void)
{
    Base bobj;
    Derived1 d1obj;
    Derived2 d2obj;

    Base *bp1 = &bobj;
    Base *bp2 = &d1obj;
    Base *bp3 = &d2obj;

    bp1->fcn();
    bp2->fcn();
    bp3->fcn();

    Derived1 *d1p = &d1obj;
    Derived2 *d2p = &d2obj;

    // bp2->fcn2(); // error, Base has no member named fcn2
    d1p->fcn2();
    d2p->fcn2();

    Base *p1 = &d2obj;
    Derived1 *p2 = &d2obj;
    Derived2 *p3 = &d2obj;

    // p1->fcn(42); // error, Base has no version of fcn that takes an int
    p2->fcn(42);
    p3->fcn(42);

    return 0;
}
