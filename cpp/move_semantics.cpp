#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

class Test
{
public:
    char *data;
    char name;
    int id;

public:
    Test(char _name)
    {
        data = new char[1024 * 1024];
        id = cnt++;
        name = _name;

        cout << "id : " << id << ", Test() with data at " << (void *)data << endl;
        cout << "name : " << name << endl;
    }

    Test(const Test &other)
    {
        data = new char[1024 * 1024];
        memcpy(data, other.data, 1024 * 1024);
        id = cnt++;
        name = other.name;

        cout << "id : " << id << ", Test(const Test &other) with data at " << (void *)data << endl;
        cout << "name : " << name << endl;
    }

    Test(Test &&other)
    {
        id = other.id;
        data = other.data;
        other.data = nullptr;

        cout << "id : " << id << ", Test(Test &&other) with data at " << (void *)data << endl;
        cout << "name : " << name << endl;
    }

    Test& operator=(const Test &other)
    {
        if (this == &other)
            return *this;

        delete []data;
        data = new char[1024 * 1024];
        memcpy(data, other.data, 1024 * 1024);
        name = other.name;

        cout << "id : " << id << ", operator=(const Test &other) with data at " << (void *)data << endl;
        cout << "name : " << name << endl;
    }

    ~Test()
    {
        cout << "id : " << id << ", ~Test() with data at " << (void *)data << endl;
        cout << "name : " << name << endl;
        delete[] data;
    }

    static int cnt;
};

int Test::cnt = 1;

int main()
{
    Test a('a');
    cout << "-------------------------------------------------------------" << endl;

    Test b('b');
    cout << "-------------------------------------------------------------" << endl;

    std::vector<Test> vec;

    vec.push_back(std::move(a));
    cout << "-------------------------------------------------------------" << endl;

    vec.push_back(std::move(b));
    cout << "-------------------------------------------------------------" << endl;

    return 0;
}
