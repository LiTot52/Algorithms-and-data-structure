// Реализовать класс Vector с поддержкой «правила пяти»,итераторами и дополнительной функциональностью согласно варианту.

// Реализация const_iterator

#include <iostream>
#include <stdexcept>
#include <utility>
#include "vector.hpp"

void printVector(const Vector<int> &v, const char *name)
{
	std::cout << name << " (size=" << v.size() << ", cap=" << v.capacity() << "): ";
	for (Vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

int main()
{
	// Конструктор по умолчанию, size, capacity, empty
	std::cout << "=== 1. Default constructor ===" << std::endl;
	Vector<int> v;
	std::cout << "size=" << v.size() << " cap=" << v.capacity()
			  << " empty=" << v.empty() << std::endl;

	// push_back и стратегия удвоения ёмкости
	std::cout << "\n=== 2. push_back (capacity doubling) ===" << std::endl;
	for (int i = 1; i <= 10; i++)
	{
		v.push_back(i);
		std::cout << "size=" << v.size() << " cap=" << v.capacity() << std::endl;
	}

	// operator[]
	std::cout << "\n=== 3. operator[] ===" << std::endl;
	std::cout << "v[5] = " << v[5] << std::endl;
	v[5] = 99;
	std::cout << "after v[5] = 99: v[5] = " << v[5] << std::endl;

	// pop_back
	std::cout << "\n=== 4. pop_back ===" << std::endl;
	v.pop_back();
	printVector(v, "v");

	// Итераторы и range-based for
	std::cout << "\n=== 5. iterator / range-based for ===" << std::endl;
	for (int x : v)
		std::cout << x << " ";
	std::cout << std::endl;

	for (Vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		*it *= 2;
	printVector(v, "v after *2");

	// const_iterator
	std::cout << "\n=== 6. const_iterator ===" << std::endl;
	const Vector<int> &cv = v;
	for (Vector<int>::const_iterator it = cv.begin(); it != cv.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << "const operator[]: cv[0] = " << cv[0] << std::endl;

	// reverse
	std::cout << "\n=== 7. reverse ===" << std::endl;
	printVector(v, "before");
	v.reverse();
	printVector(v, "after ");

	// Конструктор копирования
	std::cout << "\n=== 8. Copy constructor ===" << std::endl;
	Vector<int> a;
	for (int i = 1; i <= 3; i++)
		a.push_back(i);
	Vector<int> b = a;
	b[0] = 100;
	printVector(a, "a");
	printVector(b, "b (a[0] must stay 1)");

	// Оператор присваивания копированием + самоприсваивание
	std::cout << "\n=== 9. Copy assignment ===" << std::endl;
	Vector<int> c;
	c = a;
	c.push_back(4);
	printVector(a, "a");
	printVector(c, "c");
	a = a;
	printVector(a, "a after a = a");

	// Конструктор и оператор перемещения
	std::cout << "\n=== 10. Move constructor / move assignment ===" << std::endl;
	Vector<int> d = std::move(a);
	std::cout << "a.size()=" << a.size() << " d.size()=" << d.size() << std::endl;
	Vector<int> e;
	e = std::move(d);
	std::cout << "d.size()=" << d.size() << " e.size()=" << e.size() << std::endl;
	printVector(e, "e");

	// clear
	std::cout << "\n=== 11. clear ===" << std::endl;
	e.clear();
	std::cout << "empty=" << e.empty() << " size=" << e.size()
			  << " cap=" << e.capacity() << std::endl;

	// Конструктор с размером
	std::cout << "\n=== 12. Vector(int n) ===" << std::endl;
	Vector<int> s(5);
	printVector(s, "s");

	// Исключения
	std::cout << "\n=== 13. Exceptions ===" << std::endl;
	try
	{
		int x = s[10];
		std::cout << x << std::endl;
	}
	catch (const std::out_of_range &ex)
	{
		std::cout << "out_of_range: " << ex.what() << std::endl;
	}

	try
	{
		Vector<int> empty;
		empty.pop_back();
	}
	catch (const std::underflow_error &ex)
	{
		std::cout << "underflow_error: " << ex.what() << std::endl;
	}

	try
	{
		Vector<int> bad(-1);
	}
	catch (const std::invalid_argument &ex)
	{
		std::cout << "invalid_argument: " << ex.what() << std::endl;
	}

	return 0;
};
