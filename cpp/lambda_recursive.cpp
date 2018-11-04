#include <iostream>
#include <functional>

int main()
{
	std::function<int (int)> factorial = [&factorial](int x) -> int {
		return x <= 1 ? 1 : x * factorial(x - 1);
	};

	std::cout << "factorial(5): " << factorial(5) << std::endl;

	return 0;
}
