#include <iostream>

class Money
{
public:
    Money(double a) : amount(a) { }
    operator double() { return amount; }

private:
    double amount;
};

class Test
{
public:
    Test()
    {
        a = cnt;
        b = (char)cnt;
        c = (double)cnt;
        cnt++;
    }

    operator int()
    {
        std::cout << "Test::int() returns " << a << std::endl;
        return a;
    }
    operator char()
    {
        std::cout << "Test::char() returns " << b << std::endl;
        return b;
    }
    operator double()
    {
        std::cout << "Test::double() returns " << c << std::endl;
        return c;
    }

public:
    int a;
    char b;
    double c;

    static int cnt;
};

int Test::cnt = 1;

int main(void)
{
    Money money(100);
    double m = money;

    std::cout << m << std::endl;

    Test test[5];

    for (int i : test)
        ;

    for (char c : test)
        ;

    for (double d : test)
        ;

    return 0;
}
