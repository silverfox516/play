#include <iostream>

int main(void)
{
    int first = 10;
    int second = 5;
    int &ref = first;

    std::cout << "first  : " << first << std::endl;
    std::cout << "second : " << second << std::endl;
    std::cout << "ref    : " << ref << std::endl;

    ref = second;

    std::cout << "first  : " << first << std::endl;
    std::cout << "second : " << second << std::endl;
    std::cout << "ref    : " << ref << std::endl;

    int *ptr = &first;
    std::cout << "ptr : " << ptr << ", *ptr : " << (*ptr) << std::endl;

    second = 9;
    ptr = &second;
    std::cout << "ptr : " << ptr << ", *ptr : " << (*ptr) << std::endl;

    return 0;
}
