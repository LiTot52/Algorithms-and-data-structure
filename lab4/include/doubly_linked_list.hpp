// 1. Шаблонный класс DoublyLinkedList<T>.
// 2. Внутри: структура Node (T data, Node* prev, Node* next).
// 3. Поля: Node* head, Node* tail, int count.
// 4. Конструктор, деструктор (с clear()).
// 5. Базовые методы: push_front, push_back, pop_front, pop_back,
//    find, print, printReverse (вывод с конца), size, empty, clear.
// 6. ЗАДАНИЕ ВАРИАНТА 2:
//    - bool operator==(const DoublyLinkedList& other) const;
//      (логика та же: сравнить count, затем поэлементно)
//    - bool operator!=(const DoublyLinkedList& other) const;

#pragma once
#include <iostream>
#include <stdexcept>
#include <utility>

template <typename T>
class DoublyLinkedList
{
private:
	struct Node
	{
		T data;
		Node *prev;
		Node *next;
		Node(const T &value, Node *p = nullptr, Node *n = nullptr) : data(value), prev(p), next(n) {}
	};

	Node *head;
	Node *tail;
	int sz;

public:
	DoublyLinkedList() : head(nullptr), tail(nullptr), sz(0) {}

	~DoublyLinkedList()
	{
		clear();
	}

	//! Конструктор копирования
	DoublyLinkedList(const DoublyLinkedList &other) : head(nullptr), tail(nullptr), sz(0)
	{
		Node *current = other.head;
		while (current != nullptr)
		{
			push_back(current->data);
			current = current->next;
		}
	}

	//! SWAP
	void swap(DoublyLinkedList &other)
	{
		std::swap(head, other.head);
		std::swap(tail, other.tail);
		std::swap(sz, other.sz);
	}

	//! Копирующий operator
	DoublyLinkedList &operator=(const DoublyLinkedList &other)
	{
		if (this != &other)
		{
			DoublyLinkedList temp(other);
			swap(temp);
		}
		return *this;
	}

	//! Конструктор перемещения
	DoublyLinkedList(DoublyLinkedList &&other) noexcept
	{
		head = other.head;
		tail = other.tail;
		sz = other.sz;

		other.head = nullptr;
		other.tail = nullptr;
		other.sz = 0;
	}

	//! Перемещающий operator
	DoublyLinkedList &operator=(DoublyLinkedList &&other) noexcept
	{
		if (this != &other)
		{
			clear();
			head = other.head;
			tail = other.tail;
			sz = other.sz;

			other.head = nullptr;
			other.tail = nullptr;
			other.sz = 0;
		}
		return *this;
	}

	//! Вставка в конец
	void push_back(const T &value)
	{
		Node *newNode = new Node(value);
		if (tail == nullptr)
		{
			head = tail = newNode;
		}
		else
		{
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
		sz++;
	}

	//! Удаление из конца
	void pop_back()
	{
		if (empty())
		{
			throw std::underflow_error("Список пуст");
		}

		Node *temp = tail;
		tail = tail->prev;

		if (tail != nullptr)
		{
			tail->next = nullptr;
		}
		else
		{
			head = nullptr;
		}

		delete temp;
		sz--;
	}

	//! Вывод списка
	void print() const
	{
		Node *current = head;
		std::cout << "[ ";
		while (current != nullptr)
		{
			std::cout << current->data << " ";
			current = current->next;
		}
		std::cout << "]" << std::endl;
	}

	//! Вывод в обратном порядке
	void printReverse() const
	{
		Node *current = tail;
		std::cout << "[ ";
		while (current != nullptr)
		{
			std::cout << current->data << " ";
			current = current->prev;
		}
		std::cout << "]" << std::endl;
	}

	//! Оператор равенства
	bool operator==(const DoublyLinkedList &other) const
	{
		if (sz != other.sz)
		{
			return false;
		}

		Node *curr1 = head;
		Node *curr2 = other.head;

		while (curr1 != nullptr && curr2 != nullptr)
		{
			if (curr1->data != curr2->data)
			{
				return false;
			}
			curr1 = curr1->next;
			curr2 = curr2->next;
		}
		return true;
	}

	//! Оператор неравенства
	bool operator!=(const DoublyLinkedList &other) const
	{
		return !(*this == other);
	}

	int size() const
	{
		return sz;
	}

	bool empty() const
	{
		return sz == 0;
	}

	void clear()
	{
		while (head != nullptr)
		{
			Node *temp = head;
			head = head->next;
			delete temp;
		}
		tail = nullptr;
		sz = 0;
	}
};