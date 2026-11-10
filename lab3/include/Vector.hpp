#pragma once
// #include <iostream>
#include <stdexcept>
#include <utility>
// #include <algorithm>

template <typename T>
class Vector
{
private:
	T *data; // Указатель на динамический массив
	int sz;	 // кол-во элементов в векторе
	int cap; // кол-во элементов выделено в память

public:
	using iterator = T *;
	using const_iterator = const T *;

	iterator begin()
	{
		return data;
	}

	iterator end()
	{
		return data + sz;
	}

	const_iterator begin() const
	{
		return data;
	}

	const_iterator end() const
	{
		return data + sz;
	}

	Vector() : data(nullptr), sz(0), cap(0) {};

	~Vector()
	{
		delete[] data;
	}

	int size() const
	{
		return sz;
	}

	int capacity() const
	{
		return cap;
	}

	bool empty() const
	{
		return sz == 0;
	}

	void reserve(int newCap)
	{

		if (newCap <= cap)
		{
			return;
		}

		T *newData = new T[newCap];

		for (int i = 0; i < sz; i++)
		{
			newData[i] = data[i];
		}
		delete[] data;
		data = newData;
		cap = newCap;
	};

	void push_back(const T &value)
	{
		if (sz >= cap)
		{
			int newCap = (cap == 0) ? 1 : cap * 2;
			reserve(newCap);
		}
		data[sz] = value;
		sz++;
	};

	void pop_back()
	{
		if (empty())
		{
			throw std::underflow_error("Вектор пуст");
		}
		sz--;
	}

	T &operator[](int index)
	{
		if (index < 0 || index >= sz)
		{
			throw std::out_of_range("Индекс вне диапазона");
		}
		return data[index];
	}

	const T &operator[](int index) const
	{
		if (index < 0 || index >= sz)
		{
			throw std::out_of_range("Индекс вне диапазона");
		}
		return data[index];
	}

	void clear()
	{
		sz = 0;
	}

	//! Конструктор копирования
	Vector(const Vector &other) : data(nullptr), sz(other.sz), cap(other.cap)
	{
		data = new T[cap];
		for (int i = 0; i < sz; i++)
		{
			data[i] = other.data[i];
		}
	};

	//! SWAP
	void swap(Vector &other)
	{
		std::swap(data, other.data);
		std::swap(sz, other.sz);
		std::swap(cap, other.cap);
	}

	//! Копирующий operator
	Vector &operator=(const Vector &other)
	{
		if (this != &other)
		{
			Vector temp(other);
			swap(temp);
		}
		return *this;
	}

	//! Конструктор перемещения
	Vector(Vector &&other) noexcept
	{
		data = other.data;
		sz = other.sz;
		cap = other.cap;

		other.data = nullptr;
		other.sz = 0;
		other.cap = 0;
	}

	//! Перемещающий operator
	Vector &operator=(Vector &&other) noexcept
	{
		if (this != &other)
		{
			delete[] data;
			data = other.data;
			sz = other.sz;
			cap = other.cap;

			other.data = nullptr;
			other.sz = 0;
			other.cap = 0;
		}
		return *this;
	}

	// !REVERSE
	void reverse()
	{
		for (int i = 0; i < sz / 2; i++)
		{
			std::swap(data[i], data[sz - 1 - i]);
		}
	}

	explicit Vector(int n) : data(nullptr), sz(0), cap(0)
	{
		if (n < 0)
			throw std::invalid_argument("Аргумент не может быть отрицательным");
		if (n == 0)
			return;
		data = new T[n];
		for (int i = 0; i < n; i++)
			data[i] = T();
		sz = n;
		cap = n;
	}
};
