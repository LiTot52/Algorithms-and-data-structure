#pragma once
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

template <typename T>
class Stack
{
	T *data;	  // массив элементов
	int topIndex; // индекс вершины
	int capacity; // размер массива

	void grow()
	{
		T *bigger = new T[capacity * 2];
		for (int i = 0; i <= topIndex; i++)
			bigger[i] = data[i];
		delete[] data;
		data = bigger;
		capacity *= 2;
	}

public:
	Stack() : data(new T[4]), topIndex(-1), capacity(4) {}
	~Stack() { delete[] data; }

	Stack(const Stack &) = delete;
	Stack &operator=(const Stack &) = delete;

	void push(const T &value)
	{
		if (topIndex + 1 == capacity)
			grow();
		data[++topIndex] = value;
	}

	T pop()
	{
		if (isEmpty())
			throw std::underflow_error("Стек пуст");
		return data[topIndex--];
	}

	T top() const
	{
		if (isEmpty())
			throw std::underflow_error("Стек пуст");
		return data[topIndex];
	}

	bool isEmpty() const { return topIndex == -1; }
	int size() const { return topIndex + 1; }
};

template <typename T>
class Queue
{
	T *data;
	int head;	  // индекс первого элемента
	int count;	  // сколько элементов лежит в очереди
	int capacity; // размер массива

	void grow()
	{
		T *bigger = new T[capacity * 2];
		for (int i = 0; i < count; i++)
			bigger[i] = data[(head + i) % capacity];
		delete[] data;
		data = bigger;
		head = 0;
		capacity *= 2;
	}

public:
	Queue() : data(new T[4]), head(0), count(0), capacity(4) {}
	~Queue() { delete[] data; }

	Queue(const Queue &) = delete;
	Queue &operator=(const Queue &) = delete;

	void enqueue(const T &value)
	{
		if (count == capacity)
			grow();
		data[(head + count) % capacity] = value;
		count++;
	}

	T dequeue()
	{
		if (isEmpty())
			throw std::underflow_error("Очередь пуста");
		T value = data[head];
		head = (head + 1) % capacity;
		count--;
		return value;
	}

	T front() const
	{
		if (isEmpty())
			throw std::underflow_error("Очередь пуста");
		return data[head];
	}

	bool isEmpty() const { return count == 0; }
	int size() const { return count; }
};

template <typename T>
class Deque
{
	struct Node
	{
		T data;
		Node *prev; // сосед слева
		Node *next; // сосед справа
		Node(const T &v) : data(v), prev(nullptr), next(nullptr) {}
	};

	Node *head; // первый узел
	Node *tail; // последний узел
	int count;

public:
	Deque() : head(nullptr), tail(nullptr), count(0) {}
	~Deque()
	{
		while (!isEmpty())
			pop_front();
	}

	Deque(const Deque &) = delete;
	Deque &operator=(const Deque &) = delete;

	void push_front(const T &value)
	{
		Node *node = new Node(value);
		if (head == nullptr)
		{
			head = tail = node;
		}
		else
		{
			node->next = head;
			head->prev = node;
			head = node;
		}
		count++;
	}

	void push_back(const T &value)
	{
		Node *node = new Node(value);
		if (tail == nullptr)
		{
			head = tail = node;
		}
		else
		{
			node->prev = tail;
			tail->next = node;
			tail = node;
		}
		count++;
	}

	T pop_front()
	{
		if (isEmpty())
			throw std::underflow_error("Дек пуст");
		Node *node = head;
		T value = node->data;
		head = head->next;
		if (head != nullptr)
			head->prev = nullptr;
		else
			tail = nullptr;
		delete node;
		count--;
		return value;
	}

	T pop_back()
	{
		if (isEmpty())
			throw std::underflow_error("Дек пуст");
		Node *node = tail;
		T value = node->data;
		tail = tail->prev;
		if (tail != nullptr)
			tail->next = nullptr;
		else
			head = nullptr;
		delete node;
		count--;
		return value;
	}

	T front() const
	{
		if (isEmpty())
			throw std::underflow_error("Дек пуст");
		return head->data;
	}

	T back() const
	{
		if (isEmpty())
			throw std::underflow_error("Дек пуст");
		return tail->data;
	}

	bool isEmpty() const { return count == 0; }
	int size() const { return count; }
};

template <typename T>
class PriorityQueue
{
	T *heap;
	int count;
	int capacity;

	void grow()
	{
		T *bigger = new T[capacity * 2];
		for (int i = 0; i < count; i++)
			bigger[i] = heap[i];
		delete[] heap;
		heap = bigger;
		capacity *= 2;
	}

	void heapifyUp(int i)
	{
		while (i > 0 && heap[i] > heap[(i - 1) / 2])
		{
			std::swap(heap[i], heap[(i - 1) / 2]);
			i = (i - 1) / 2;
		}
	}

	void heapifyDown(int i)
	{
		while (true)
		{
			int left = 2 * i + 1;
			int right = 2 * i + 2;
			int largest = i;
			if (left < count && heap[left] > heap[largest])
				largest = left;
			if (right < count && heap[right] > heap[largest])
				largest = right;
			if (largest == i)
				break;
			std::swap(heap[i], heap[largest]);
			i = largest;
		}
	}

public:
	PriorityQueue() : heap(new T[4]), count(0), capacity(4) {}
	~PriorityQueue() { delete[] heap; }

	PriorityQueue(const PriorityQueue &) = delete;
	PriorityQueue &operator=(const PriorityQueue &) = delete;

	void push(const T &value)
	{
		if (count == capacity)
			grow();
		heap[count] = value;
		heapifyUp(count);
		count++;
	}

	T pop()
	{
		if (isEmpty())
			throw std::underflow_error("Приоритетная очередь пуста");
		T maxValue = heap[0];
		heap[0] = heap[count - 1];
		count--;
		heapifyDown(0);
		return maxValue;
	}

	T top() const
	{
		if (isEmpty())
			throw std::underflow_error("Приоритетная очередь пуста");
		return heap[0];
	}

	bool isEmpty() const { return count == 0; }
	int size() const { return count; }
};

inline double evalRPN(const std::string &expr)
{
	Stack<double> st;
	std::istringstream in(expr);
	std::string token;

	while (in >> token)
	{
		bool isOp = token.size() == 1 &&
					(token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/');

		if (isOp)
		{
			if (st.size() < 2)
				throw std::invalid_argument("Не хватает операндов для " + token);
			double b = st.pop();
			double a = st.pop();
			if (token[0] == '+')
				st.push(a + b);
			else if (token[0] == '-')
				st.push(a - b);
			else if (token[0] == '*')
				st.push(a * b);
			else
			{
				if (b == 0)
					throw std::domain_error("Деление на ноль");
				st.push(a / b);
			}
		}
		else
		{
			std::size_t pos = 0;
			double value = 0;
			try
			{
				value = std::stod(token, &pos);
			}
			catch (const std::exception &)
			{
				throw std::invalid_argument("Некорректный токен: " + token);
			}
			if (pos != token.size())
				throw std::invalid_argument("Некорректный токен: " + token);
			st.push(value);
		}
	}

	if (st.size() != 1)
		throw std::invalid_argument("Некорректное выражение");
	return st.pop();
}

template <typename T>
class TwoStackQueue
{
	Stack<T> inStack;
	Stack<T> outStack;

	void transfer()
	{
		if (outStack.isEmpty())
			while (!inStack.isEmpty())
				outStack.push(inStack.pop());
	}

public:
	void enqueue(const T &value) { inStack.push(value); }

	T dequeue()
	{
		transfer();
		if (outStack.isEmpty())
			throw std::underflow_error("Очередь пуста");
		return outStack.pop();
	}

	T front()
	{
		transfer();
		if (outStack.isEmpty())
			throw std::underflow_error("Очередь пуста");
		return outStack.top();
	}

	bool isEmpty() const { return inStack.isEmpty() && outStack.isEmpty(); }
	int size() const { return inStack.size() + outStack.size(); }
};

template <typename T>
class FixedDeque
{
	T *data;
	int head;	  // индекс первого элемента
	int count;	  // сколько элементов лежит в деке
	int capacity; // размер массива, не меняется

public:
	explicit FixedDeque(int cap) : data(nullptr), head(0), count(0), capacity(cap)
	{
		if (cap <= 0)
			throw std::invalid_argument("Ёмкость должна быть положительной");
		data = new T[capacity];
	}
	~FixedDeque() { delete[] data; }

	FixedDeque(const FixedDeque &) = delete;
	FixedDeque &operator=(const FixedDeque &) = delete;

	void push_front(const T &value)
	{
		if (isFull())
			throw std::overflow_error("Дек переполнен");
		head = (head - 1 + capacity) % capacity;
		data[head] = value;
		count++;
	}

	void push_back(const T &value)
	{
		if (isFull())
			throw std::overflow_error("Дек переполнен");
		data[(head + count) % capacity] = value;
		count++;
	}

	T pop_front()
	{
		if (isEmpty())
			throw std::underflow_error("Дек пуст");
		T value = data[head];
		head = (head + 1) % capacity;
		count--;
		return value;
	}

	T pop_back()
	{
		if (isEmpty())
			throw std::underflow_error("Дек пуст");
		T value = data[(head + count - 1) % capacity];
		count--;
		return value;
	}

	T front() const
	{
		if (isEmpty())
			throw std::underflow_error("Дек пуст");
		return data[head];
	}

	T back() const
	{
		if (isEmpty())
			throw std::underflow_error("Дек пуст");
		return data[(head + count - 1) % capacity];
	}

	bool isEmpty() const { return count == 0; }
	bool isFull() const { return count == capacity; }
	int size() const { return count; }
};

template <typename T>
void kSmallest(const T *arr, int n, int k, T *result)
{
	if (n < 0 || k < 0 || k > n)
		throw std::invalid_argument("Некорректные n или k");

	PriorityQueue<T> heap;
	for (int i = 0; i < n; i++)
	{
		if (heap.size() < k)
			heap.push(arr[i]);
		else if (arr[i] < heap.top())
		{
			heap.pop();
			heap.push(arr[i]);
		}
	}

	for (int i = k - 1; i >= 0; i--)
		result[i] = heap.pop();
}