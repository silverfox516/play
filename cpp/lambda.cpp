#include <iostream>
#include <functional>
#include <vector>

template<typename T>
void templateFunc(T func)
{
	func();
}

std::function<void (void)> getLambda()
{
	return []() { std::cout << "Gutten tag!" << std::endl; };
}

int main()
{
	auto foo = []() { std::cout << "Hello lambda!" << std::endl; };
	templateFunc(foo);


	auto introduce = [](std::string name) {
		std::cout << "My name is " << name << std::endl;
	};
	introduce("Jinsoo Heo");


	auto boo = getLambda();
	boo();


	std::vector<std::function<void (void)>> funcs;
	funcs.push_back(foo);
	funcs.push_back(getLambda());
	std::cout << "-------- function in container -------" << std::endl;
	for (auto& func : funcs) {
		func();
	}


	auto mii = [] { return 3.14; };
	auto kii = []() -> float { return 3.14; };
	float m = mii();
	float k = kii();

	return 0;
}
