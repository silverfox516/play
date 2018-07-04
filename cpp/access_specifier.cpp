#include <iostream>
#include <string>

class Base
{
public: /* affect to user accessibility */
    Base(std::string a, std::string b, std::string c)
        : public_member(a), protected_member(b), private_member(c) { }
public:
    std::string public_member;
protected:
    std::string protected_member;
private:
    std::string private_member;
};

class PublicDerived : public /* affect to access specifier of base class */ Base
{
public:
    PublicDerived(std::string a, std::string b, std::string c)
        : Base(a, b, c) {
        }
    void print() {
        std::cout << public_member << std::endl;
        std::cout << protected_member << std::endl;
        // std::cout << private_member << std::endl; // error, drived class cannot access private members of base class
    }
};

class ProtectedDerived : protected Base
{
public:
    ProtectedDerived(std::string a, std::string b, std::string c)
        : Base(a, b, c) {
        }
    void print() {
        std::cout << public_member << std::endl;
        std::cout << protected_member << std::endl;
        // std::cout << private_member << std::endl; // error, drived class cannot access private members of base class
    }
};

class PrivateDerived : private Base
{
public:
    PrivateDerived(std::string a, std::string b, std::string c)
        : Base(a, b, c) {
        }
    void print() {
        std::cout << public_member << std::endl;
        std::cout << protected_member << std::endl;
        // std::cout << private_member << std::endl; // error, drived class cannot access private members of base class
    }
};

int main(void)
{
    PublicDerived publicDerived("a", "b", "c");

    std::cout << publicDerived.public_member << std::endl;
    // std::cout << publicDerived.protected_member << std::endl; // error, user cannot access protected members
    // std::cout << publicDerived.private_member << std::endl; // error, user cannot access protected members
    publicDerived.print();

    ProtectedDerived protectedDerived("aa", "bb", "cc");
    // std::cout << protectedDerived.public_member << std::endl; // error, user cannot access protected members, public_member is converted to protected
    protectedDerived.print();

    PrivateDerived privateDerived("aaa", "bbb", "ccc");
    privateDerived.print();

    return 0;
}
