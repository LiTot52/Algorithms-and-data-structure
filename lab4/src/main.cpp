// 1. #include "singly_linked_list.hpp" и "doubly_linked_list.hpp".
// 2. Создать 2 ОДИНАКОВЫХ списка (Singly), наполнить push_back.
//    Проверить: list1 == list2 (должно быть true/1).
// 3. Создать 3-й список с другим элементом.
//    Проверить: list1 != list3 (должно быть true/1).
// 4. Повторить то же самое для DoublyLinkedList.
// 5. Показать работу print() и printReverse() (для двусвязного).

#include <iostream>
#include "../include/singly_linked_list.hpp"
#include "../include/doubly_linked_list.hpp"

int main()
{
	setlocale(LC_ALL, "ru");

	std::cout << "--- Тест SinglyLinkedList (Вариант 2) ---" << std::endl;
	SinglyLinkedList<int> s1;
	s1.push_back(10);
	s1.push_back(20);

	SinglyLinkedList<int> s2;
	s2.push_back(10);
	s2.push_back(20);

	SinglyLinkedList<int> s3;
	s3.push_back(10);
	s3.push_back(99);

	std::cout << "Список s1: ";
	s1.print();

	std::cout << "s1 == s2: " << (s1 == s2) << " (ожидается 1)" << std::endl;
	std::cout << "s1 != s3: " << (s1 != s3) << " (ожидается 1)" << std::endl;

	std::cout << "\n--- Тест DoublyLinkedList (Вариант 2) ---" << std::endl;
	DoublyLinkedList<int> d1;
	d1.push_back(1);
	d1.push_back(2);
	d1.push_back(3);

	DoublyLinkedList<int> d2;
	d2.push_back(1);
	d2.push_back(2);
	d2.push_back(3);

	std::cout << "Список d1 (прямой): ";
	d1.print();
	std::cout << "Список d1 (обратный): ";
	d1.printReverse();

	std::cout << "d1 == d2: " << (d1 == d2) << " (ожидается 1)" << std::endl;

	return 0;
}