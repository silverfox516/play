#include <iostream>
#include <memory>
#include <string>

// g++ unique_ptr.cpp --std=c++14

using namespace std;

class Person
{
private:
    string name_;
    int age_;

public:
    Person(const string &name, int age);
    ~Person() { std::cout << "~Person() : " << name_ << ", " << age_ << std::endl; }
    void showPersonInfo();
};

int main(void)
{
    unique_ptr /* c++11 */ <Person> hong = make_unique /* c++14 */ <Person>("gildong", 29);
    hong->showPersonInfo();

    Person *stupid_hong = new Person("killdung", 29);
    stupid_hong->showPersonInfo();

    return 0;
}

Person::Person(const string &name, int age) :
    name_(name),
    age_(age)
{
    std::cout << "Person() : " << name_ << ", " << age_ << std::endl;
}

void Person::showPersonInfo()
{
    std::cout << name_ << "'s age is " << age_ << "." << std::endl;
}
