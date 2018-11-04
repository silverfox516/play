#include <array>
#include <algorithm>
#include <iostream>
#include <string>

int gsum = 0;

class Person
{
public:
	Person(std::string name) : name(name) {}
	void introduce() {
		[this]() { std::cout << "My name is " << name << std::endl; }();
	}

private:
	std::string name;
};

int main()
{
	std::array<int, 5> numbers = { 1, 2, 3, 4, 5 };
	int sum = 0;

	/*
	 * [a,&b] a를 복사로 캡처, b를 참조로 캡처.
	 * [this] 현재 객체를 참조로 캡처.
	 * [&] 몸통에서 쓰이는 모든 변수나 상수를 참조로 캡처하고 현재 객체를 참조로 캡처.
	 * [=] 몸통에서 쓰이는 모든 변수나 상수를 복사로 캡처하고 현재 객체를 참조로 캡처.
	 * [] 아무것도 캡처하지 않음.
	 */

	//std::for_each(numbers.begin(), numbers.end(), [sum](int& number) /* constexpr */ {
	//std::for_each(numbers.begin(), numbers.end(), [sum](int& number) mutable {
	std::for_each(numbers.begin(), numbers.end(), [&sum](int& number) {
			sum += number;
			});
	std::cout << sum << std::endl;


	std::for_each(numbers.begin(), numbers.end(), [&](int& number) {
			gsum += number;
			});
	std::cout << gsum << std::endl;


	std::string name = "Jinsoo Heo";
	[name]() {
		std::cout << "My name is " << name << std::endl;
	}();


	int x = 0;
 	char y = 'j';
	double z = 3.14;
	std::string w = "Jinsoo Heo";

	auto foo = [&x, &y, z, w]() {};


	int a, b, c;

	[&, a, b]() {}();
	[=, &c]() {}();
	[&, &a]() {}();	// wrong
	[=, b]() {}();	// wrong


	Person* devkoriel = new Person("Lion");
	devkoriel->introduce();

	return 0;
}
