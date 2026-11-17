// Реализовать класс Vector с поддержкой «правила пяти», итераторами и дополнительной функциональностью согласно варианту.
// Реализация const_iterator

#include <iostream>
#include <stdexcept>
#include <utility>
#include "../include/Vector.hpp"

void print(const char *name, const Vector<int> &v)
{
	std::cout << name << ": [";
	for (Vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
		std::cout << *it << (it + 1 != v.end() ? " " : "");
	std::cout << "] size=" << v.size() << " cap=" << v.capacity() << std::endl;
}

int main()
{
	// 1. Конструктор по умолчанию.
	Vector<int> v;
	print("1. пустой         ", v);

	// 2. push_back
	for (int i = 1; i <= 5; i++)
		v.push_back(i);
	print("2. push_back 1..5 ", v);

	// 3. operator[]
	v[2] = 99;
	print("3. v[2] = 99      ", v);

	// 4. pop_back.
	v.pop_back();
	print("4. pop_back       ", v);

	// 5. Обычный итератор
	for (Vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		*it *= 2;
	print("5. iterator *2    ", v);

	// 6. Константный оператор
	const Vector<int> &cv = v;
	std::cout << "6. const cv[0]    : " << cv[0] << std::endl;

	// 7. Цикл
	std::cout << "7. range-for      : ";
	for (int x : v)
		std::cout << x << " ";
	std::cout << std::endl;

	// 8. reverse.
	v.reverse();
	print("8. reverse        ", v);

	// 9. Конструктор копирования.
	Vector<int> a;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	Vector<int> b = a;
	b[0] = 100;
	print("9. a (не изменился)", a);
	print("   b (копия)      ", b);

	// 10. Копирующее присваивание и самоприсваивание.
	Vector<int> c;
	c = a;
	c.push_back(4);
	a = a;
	print("10. c = a, +4     ", c);
	print("    a = a         ", a);

	// 11. Конструктор перемещения и перемещающее присваивание.
	Vector<int> d = std::move(a);
	Vector<int> e;
	e = std::move(d);
	print("11. a после move  ", a);
	print("    e (получил)   ", e);

	// 12. clear.
	e.clear();
	print("12. clear         ", e);

	// 13. Конструктор Vector(int n).
	Vector<int> s(3);
	print("13. Vector(3)     ", s);

	// 14. Исключения.
	try
	{
		s[10];
	}
	catch (const std::out_of_range &ex)
	{
		std::cout << "14. out_of_range  : " << ex.what() << std::endl;
	}

	// pop_back
	try
	{
		Vector<int> empty;
		empty.pop_back();
	}
	catch (const std::underflow_error &ex)
	{
		std::cout << "    underflow_error: " << ex.what() << std::endl;
	}

	// Отрицательный размер в конструкторе
	try
	{
		Vector<int> bad(-1);
	}
	catch (const std::invalid_argument &ex)
	{
		std::cout << "    invalid_argument: " << ex.what() << std::endl;
	}

	return 0;
}