// Реализовать шаблонный контейнер с заданной

// List<T>
// push_front, push_back, pop_front,
// pop_back, size, insert, erase

#include <iostream>
#include <string>
#include "../include/List.hpp"

int main()
{
	std::cout << "=== Тестирование шаблонного List<T> ===\n\n";

	//! Список целых чисел
	List<int> intList;
	intList.push_back(10);
	intList.push_back(20);
	intList.push_front(5);

	std::cout << "Исходный список int: ";
	intList.print();
	std::cout << "Размер: " << intList.size() << "\n\n";

	//! Вставка и удаление
	intList.insert(1, 7);
	std::cout << "После insert(1, 7): ";
	intList.print();

	intList.erase(2);
	std::cout << "После erase(2): ";
	intList.print();

	intList.pop_front();
	intList.pop_back();
	std::cout << "После pop_front и pop_back: ";
	intList.print();
	std::cout << "\n";

	//! Список строк
	List<std::string> stringList;
	stringList.push_front("Мир");
	stringList.push_front("Привет");
	stringList.push_back("!");

	std::cout << "Список string: ";
	stringList.print();
	return 0;
}