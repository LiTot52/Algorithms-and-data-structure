#pragma once // Защита от повторения
#include <iostream>
#include <stdexcept>

template <typename T>
class List
{
private:
	struct Node
	{
		T data;
		Node *prev;
		Node *next;

		Node(const T &value) : data(value), prev(nullptr), next(nullptr) {}
	};

	Node *head_;
	Node *tail_;
	int size_;

public:
	//! Конструктор
	List() : head_(nullptr), tail_(nullptr), size_(0) {};

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
		tail_ = nullptr;
		size_ = 0;
	}

	//! Размер списка
	int size() const
	{
		return size_;
	}

	//! Добавление в начало
	void push_front(const T &value)
	{
		Node *newNode = new Node(value);
		if (head_ == nullptr)
		{
			head_ = tail_ = newNode;
		}
		else
		{
			newNode->next = head_;
			head_->prev = newNode;
			head_ = newNode;
		}
		size_++;
	}

	//! Добавление в конец
	void push_back(const T &value)
	{
		Node *newNode = new Node(value);
		if (tail_ == nullptr)
		{
			head_ = tail_ = newNode;
		}
		else
		{
			newNode->prev = tail_;
			tail_->next = newNode;
			tail_ = newNode;
		}
		size_++;
	}

	//! Удаление из начала
	void pop_front()
	{
		if (head_ == nullptr)
			return;

		Node *temp = head_;
		head_ = head_->next;
		if (head_ != nullptr)
		{
			head_->prev = nullptr;
		}
		else
		{
			tail_ = nullptr;
		}
		delete temp;
		size_--;
	}

	//! Удаление из конца
	void pop_back()
	{
		if (tail_ == nullptr)
			return;

		Node *temp = tail_;
		tail_ = tail_->prev;
		if (tail_ != nullptr)
		{
			tail_->next = nullptr;
		}
		else
		{
			head_ = nullptr;
		}
		delete temp;
		size_--;
	}

	//! Вставка по индексу
	void insert(int index, const T &value)
	{
		if (index < 0 || index > size_)
		{
			throw std::out_of_range("Индекс вне диапазона");
		}
		if (index == 0)
		{
			push_front(value);
			return;
		}
		if (index == size_)
		{
			push_back(value);
			return;
		}

		Node *current = head_;
		for (int i = 0; i < index - 1; ++i)
		{
			current = current->next;
		}

		Node *newNode = new Node(value);
		newNode->next = current->next;
		newNode->prev = current;
		current->next->prev = newNode;
		current->next = newNode;
		size_++;
	}

	//! Удаление по индексу
	void erase(int index)
	{
		if (index < 0 || index >= size_)
		{
			throw std::out_of_range("Индекс вне диапазона");
		}

		if (index == 0)
		{
			pop_front();
			return;
		}
		if (index == size_ - 1)
		{
			pop_back();
			return;
		}

		Node *current = head_;
		for (int i = 0; i < index; ++i)
		{
			current = current->next;
		}

		current->prev->next = current->next;
		current->next->prev = current->prev;
		delete current;
		size_--;
	}

	//! Вывод в консоль
	void print() const
	{
		Node *current = head_;
		std::cout << "[ ";
		while (current != nullptr)
		{
			std::cout << current->data << " ";
			current = current->next;
		}
		std::cout << "]\n";
	}
};