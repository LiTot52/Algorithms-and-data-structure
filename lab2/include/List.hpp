// Объявление шаблона

#pragma once // Защита от повторения
#include <iostream>
#include <stdexcept>

// Шаблонный класс двусвязного списка
template <typename T>
class List
{
private:
	struct List
	{
		T data;
		Node *prev;
		Node *next;

		Node(const T &value) : data(value), prev(nullptr), next(nullptr) {}
	};

	Node *head_;
	Node *tali_;
	int size_;

public:
	//! Конструктор

	List() : head_(nullptr), tali_(nullptr), size_(0) {};

	//! Деструктор
	~List()
	{
		clear();
	};

	//! Очистка списка
	void clear()
	{
		Node *current = head_;
		while (current != nullptr)
		{
			Node *next = current->next;
			delete current;
			current = next;
		}
		head_ = nullptr;
		tali_ = nullptr;
		size_ = 0;
	}

	//! Размер списка
	ins size() const
	{
		return size_;
	}

	// Добавление в начало — O(1)
	// Добавление в конец — O(1)
	// Удаление из начала — O(1)
	// Удаление из конца — O(1)
	// Вставка по индексу — O(n)
	// Удаление по индексу — O(n)
	// вывода в консоль
};
