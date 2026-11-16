// 1. Шаблонный класс SinglyLinkedList<T>.
// 2. Внутри: структура Node (T data, Node* next).
// 3. Поля: Node* head, Node* tail, int count.
// 4. Конструктор, деструктор (с clear()).
// 5. Базовые методы: push_front, push_back, pop_front, pop_back,
//    find, print, size, empty, clear.
// 6. ЗАДАНИЕ ВАРИАНТА 2:
//    - bool operator==(const SinglyLinkedList& other) const;
//      (сравнить count, затем циклом пройтись и сравнить data)
//    - bool operator!=(const SinglyLinkedList& other) const;
//      (вернуть !(*this == other))

#pragma once
#include <iostream>
#include <stdexcept>
#include <utility>

template <typename T>
class SinglyLinkedList
{
private:
	struct Node
	{
		T data;
		Node *next;
		Node(const T &value, Node *n = nullptr) : data(value), next(n) {}
	};

	Node *head;
	Node *tail;
	int sz;

public:
	SinglyLinkedList() : head(nullptr), tail(nullptr), sz(0) {}

	~SinglyLinkedList()
	{
		clear();
	}

	//! Конструктор копирования
	SinglyLinkedList(const SinglyLinkedList &other) : head(nullptr), tail(nullptr), sz(0)
	{
		Node *current = other.head;
		while (current != nullptr)
		{
			push_back(current->data);
			current = current->next;
		}
	}

	//! SWAP
	void swap(SinglyLinkedList &other)
	{
		std::swap(head, other.head);
		std::swap(tail, other.tail);
		std::swap(sz, other.sz);
	}

	//! Копирующий operator
	SinglyLinkedList &operator=(const SinglyLinkedList &other)
	{
		if (this != &other)
		{
			SinglyLinkedList temp(other);
			swap(temp);
		}
		return *this;
	}

	//! Конструктор перемещения
	SinglyLinkedList(SinglyLinkedList &&other) noexcept
	{
		head = other.head;
		tail = other.tail;
		sz = other.sz;

		other.head = nullptr;
		other.tail = nullptr;
		other.sz = 0;
	}

	//! Перемещающий operator
	SinglyLinkedList &operator=(SinglyLinkedList &&other) noexcept
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
		if (head == nullptr)
		{
			head = tail = newNode;
		}
		else
		{
			tail->next = newNode;
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

		if (head == tail)
		{
			delete head;
			head = tail = nullptr;
		}
		else
		{
			Node *current = head;
			while (current->next != tail)
			{
				current = current->next;
			}
			delete tail;
			tail = current;
			tail->next = nullptr;
		}
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

	//! Оператор равенства
	bool operator==(const SinglyLinkedList &other) const
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
	bool operator!=(const SinglyLinkedList &other) const
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