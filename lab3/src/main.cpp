// Реализовать класс Vector с поддержкой «правила пяти»,итераторами и дополнительной функциональностью согласно варианту.

// Реализация const_iterator

#include <iostream>
#include "../include/Vector.hpp"

int main()
{

	Vector<int> v(5);
	std::cout << v.size() << " " << v.capacity() << std::endl; // 5 5
	for (int x : v)
		std::cout << x << " "; // 0 0 0 0 0
	std::cout << std::endl;

	try
	{
		Vector<int> bad(-1);
	}
	catch (const std::invalid_argument &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	return 0;
}