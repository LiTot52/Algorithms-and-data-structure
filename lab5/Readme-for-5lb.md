# Лабораторная работа №5
# Тема: Стек, очередь, дек, приоритетная очередь
 
**Студент:** Геграев Ислам Русланович  
**Группа:** ПИЖ-б-о-25-2  
**Вариант:** 2  
**Уровень:** Продвинутый  
**Технологии:** C++17
 
## Содержание
 
- [Лабораторная работа №5](#лабораторная-работа-5)
- [Тема: Стек, очередь, дек, приоритетная очередь](#тема-стек-очередь-дек-приоритетная-очередь)
	- [Содержание](#содержание)
	- [Цель работы](#цель-работы)
	- [Теоретическое обоснование](#теоретическое-обоснование)
	- [Постановка задачи](#постановка-задачи)
	- [Листинг программы](#листинг-программы)
		- [structures.hpp](#structureshpp)
		- [main.cpp](#maincpp)
	- [Анализ сложности](#анализ-сложности)
	- [Вывод](#вывод)
	- [Ответы на контрольные вопросы](#ответы-на-контрольные-вопросы)
## Цель работы
 
1. Реализовать основные линейные структуры данных: стек, очередь, дек и приоритетную очередь.
2. Освоить принципы LIFO (стек) и FIFO (очередь).
3. Научиться реализовывать эти структуры на основе динамического массива, кольцевого буфера и связного списка.
4. Изучить применение стека для решения задач (вычисление выражения в обратной польской записи).
5. Реализовать приоритетную очередь на основе двоичной кучи (heap).
## Теоретическое обоснование
 
**Стек (Stack)** — структура данных, работающая по принципу **LIFO** (Last In — First Out, «последним пришёл — первым ушёл»). Элементы добавляются и удаляются только с одного конца — вершины стека. Аналогия: стопка тарелок.
 
```text
push(1): [1]
push(2): [1, 2]
push(3): [1, 2, 3]
pop():   [1, 2]      (возвращает 3)
top():   [1, 2]      (возвращает 2, не удаляя)
```
 
**Очередь (Queue)** — структура данных, работающая по принципу **FIFO** (First In — First Out, «первым пришёл — первым ушёл»). Элементы добавляются в конец, а извлекаются из начала. Аналогия: очередь в магазине.
 
```text
enqueue(1): [1]
enqueue(2): [1, 2]
enqueue(3): [1, 2, 3]
dequeue():  [2, 3]   (возвращает 1)
front():    [2, 3]   (возвращает 2, не удаляя)
```
 
**Дек (Deque, Double-Ended Queue)** — двусторонняя очередь: элементы можно добавлять и удалять с обоих концов за O(1). Дек обобщает и стек, и очередь.
 
**Приоритетная очередь (Priority Queue)** — структура данных, в которой каждый элемент имеет приоритет, а извлекается всегда элемент с наибольшим приоритетом. Обычно реализуется на **двоичной куче** (max-heap) — почти полном двоичном дереве, в котором значение каждого узла не меньше значений его потомков. Куча хранится в массиве: для элемента с индексом `i` левый потомок имеет индекс `2i + 1`, правый — `2i + 2`, родитель — `(i - 1) / 2`.
 
```text
        50
       /  \
     20    30          массив: [ 50 20 30 10 ]
    /
  10
```
 
**Способы реализации, использованные в работе:**
 
| Структура          | Реализация                                      |
| ------------------ | ----------------------------------------------- |
| `Stack<T>`         | динамический массив с удвоением ёмкости         |
| `Queue<T>`         | кольцевой буфер с удвоением ёмкости             |
| `Deque<T>`         | двусвязный список                               |
| `PriorityQueue<T>` | двоичная куча (max-heap) в динамическом массиве |
| `TwoStackQueue<T>` | два стека `Stack<T>`                            |
| `FixedDeque<T>`    | кольцевой буфер фиксированной ёмкости           |
 
**Кольцевой буфер:** массив рассматривается как замкнутый — индекс после последнего элемента снова указывает на начало массива. Индексы вычисляются по формуле `(frontIndex + i) % capacity`, поэтому ни добавление, ни удаление не требуют сдвига элементов.
 
**Управление памятью:** память выделяется динамически (`new` / `new[]`) и освобождается в деструкторе. Копирование объектов запрещено (`= delete`), чтобы два объекта не освободили один и тот же массив (двойное освобождение).
 
## Постановка задачи
 
**Вариант 2**
 
| Структура            | Задание                                                                         |
| -------------------- | ------------------------------------------------------------------------------- |
| Стек                 | Вычислить значение выражения в обратной польской записи (например, `3 4 + 5 *`) |
| Очередь              | Реализовать очередь на двух стеках                                              |
| Дек                  | Реализовать дек с фиксированной ёмкостью (кольцевой буфер)                      |
| Приоритетная очередь | Найти K наименьших элементов в массиве                                          |
 
**Продвинутый уровень:**
 
* Реализовать шаблонные классы `Stack<T>`, `Queue<T>`, `Deque<T>`, `PriorityQueue<T>` без использования STL-контейнеров.
* Предусмотреть обработку ошибок: исключения при обращении к пустой структуре и при переполнении дека фиксированной ёмкости.
* Защитить классы от двойного освобождения памяти (запрет копирования).
* Покрыть реализацию проверками, включая граничные случаи.
## Листинг программы
 
### structures.hpp
 
```cpp
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
 
	/
	Stack(const Stack &) = delete;
	Stack &operator=(const Stack &) = delete;
 
	// Добавить на вершину, O(1)
	void push(const T &value)
	{
		if (topIndex + 1 == capacity)
			grow();
		data[++topIndex] = value;
	}
 
	// Убрать с вершины и вернуть, O(1)
	T pop()
	{
		if (isEmpty())
			throw std::underflow_error("Стек пуст");
		return data[topIndex--];
	}
 
	// Посмотреть вершину, O(1)
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
 
	// Добавить в конец, O(1)
	void enqueue(const T &value)
	{
		if (count == capacity)
			grow();
		data[(head + count) % capacity] = value; 
		count++;
	}
 
	// Убрать из начала и вернуть, O(1)
	T dequeue()
	{
		if (isEmpty())
			throw std::underflow_error("Очередь пуста");
		T value = data[head];
		head = (head + 1) % capacity;
		count--;
		return value;
	}
 
	// Посмотреть первый элемент, O(1)
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
		Node *prev; 
		Node *next;
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
```
 
### main.cpp
 
```cpp
#include <clocale>
#include <iostream>
#include <string>
#include "structures.hpp"
 
using namespace std;
 
static int failed = 0; 
 

static void check(const string &name, bool ok)
{
	cout << (ok ? "[OK]   " : "[FAIL] ") << name << endl;
	if (!ok)
		failed++;
}
 

template <typename Ex, typename F>
static bool throwsEx(F f)
{
	try
	{
		f();
	}
	catch (const Ex &)
	{
		return true;
	}
	catch (...)
	{
		return false;
	}
	return false;
}
 
int main()
{
	setlocale(LC_ALL, "ru");
 
	
	cout << "=== 1. Стек ===" << endl;
	Stack<int> s;
	s.push(1);
	s.push(2);
	s.push(3);
	check("pop() = 3 (последним пришёл — первым ушёл)", s.pop() == 3);
	check("top() = 2, элемент остаётся в стеке", s.top() == 2 && s.size() == 2);
 
	Stack<int> bigStack;
	for (int i = 0; i < 20; i++)
		bigStack.push(i);
	check("массив расширяется: 20 элементов", bigStack.size() == 20 && bigStack.top() == 19);
 
	Stack<int> emptyStack;
	check("pop() из пустого стека -> исключение", throwsEx<underflow_error>([&] { emptyStack.pop(); }));
	check("top() из пустого стека -> исключение", throwsEx<underflow_error>([&] { emptyStack.top(); }));
 
	cout << "\nОбратная польская запись: \"3 4 + 5 *\" = " << evalRPN("3 4 + 5 *") << endl;
	check("3 4 + 5 * = 35", evalRPN("3 4 + 5 *") == 35);
	check("5 1 2 + 4 * + 3 - = 14", evalRPN("5 1 2 + 4 * + 3 -") == 14);
	check("10 2 / = 5", evalRPN("10 2 /") == 5);
	check("-5 3 + = -2", evalRPN("-5 3 +") == -2);
	check("\"1 +\" -> исключение", throwsEx<invalid_argument>([] { evalRPN("1 +"); }));
	check("\"4 0 /\" -> исключение", throwsEx<domain_error>([] { evalRPN("4 0 /"); }));
	check("\"1 2\" -> исключение", throwsEx<invalid_argument>([] { evalRPN("1 2"); }));
	check("\"1 a +\" -> исключение", throwsEx<invalid_argument>([] { evalRPN("1 a +"); }));
 
	
	cout << "\n=== 2. Очередь ===" << endl;
	Queue<int> q;
	q.enqueue(10);
	q.enqueue(20);
	q.enqueue(30);
	check("dequeue() = 10 (первым пришёл — первым ушёл)", q.dequeue() == 10);
	check("front() = 20, элемент остаётся в очереди", q.front() == 20 && q.size() == 2);
 
	Queue<int> ring;
	for (int i = 0; i < 4; i++)
		ring.enqueue(i); 
	ring.dequeue();
	ring.dequeue();
	for (int i = 4; i < 10; i++)
		ring.enqueue(i); 
	bool order = true;
	for (int i = 2; i < 10; i++)
		if (ring.dequeue() != i)
			order = false;
	check("кольцевой буфер: порядок 2..9 сохранился", order);
 
	Queue<int> emptyQueue;
	check("dequeue() из пустой очереди -> исключение", throwsEx<underflow_error>([&] { emptyQueue.dequeue(); }));
	check("front() из пустой очереди -> исключение", throwsEx<underflow_error>([&] { emptyQueue.front(); }));
 
	cout << "\nОчередь на двух стеках:" << endl;
	TwoStackQueue<int> tsq;
	tsq.enqueue(1);
	tsq.enqueue(2);
	tsq.enqueue(3);
	check("dequeue() = 1", tsq.dequeue() == 1);
	tsq.enqueue(4);
	check("front() = 2", tsq.front() == 2);
	check("порядок FIFO: 2 3 4", tsq.dequeue() == 2 && tsq.dequeue() == 3 && tsq.dequeue() == 4);
	check("очередь пуста", tsq.isEmpty());
	check("dequeue() из пустой -> исключение", throwsEx<underflow_error>([&] { tsq.dequeue(); }));
 
	
	cout << "\n=== 3. Дек ===" << endl;
	Deque<int> d;
	d.push_back(2);
	d.push_back(3);
	d.push_front(1); 
	check("front() = 1, back() = 3", d.front() == 1 && d.back() == 3);
	check("pop_front() = 1", d.pop_front() == 1);
	check("pop_back() = 3", d.pop_back() == 3);
	check("pop_back() = 2, дек пуст", d.pop_back() == 2 && d.isEmpty());
	check("pop_front() из пустого дека -> исключение", throwsEx<underflow_error>([&] { d.pop_front(); }));
	check("pop_back() из пустого дека -> исключение", throwsEx<underflow_error>([&] { d.pop_back(); }));
 
	cout << "\nДек фиксированной ёмкости (3 места):" << endl;
	FixedDeque<int> fd(3);
	fd.push_back(1);
	fd.push_back(2);
	fd.push_front(0);
	check("дек заполнен", fd.isFull() && fd.size() == 3);
	check("push_back() в полный дек -> исключение", throwsEx<overflow_error>([&] { fd.push_back(5); }));
	check("push_front() в полный дек -> исключение", throwsEx<overflow_error>([&] { fd.push_front(5); }));
	check("pop_front() = 0", fd.pop_front() == 0);
	check("pop_back() = 2", fd.pop_back() == 2);
	fd.push_front(9);
	fd.push_front(8); 
	check("кольцо: front = 8, back = 1", fd.front() == 8 && fd.back() == 1);
	check("порядок: 8 9 1", fd.pop_front() == 8 && fd.pop_front() == 9 && fd.pop_front() == 1);
	check("pop_front() из пустого -> исключение", throwsEx<underflow_error>([&] { fd.pop_front(); }));
	check("ёмкость 0 -> исключение", throwsEx<invalid_argument>([] { FixedDeque<int> bad(0); }));
 
	
	cout << "\n=== 4. Приоритетная очередь ===" << endl;
	PriorityQueue<int> pq;
	pq.push(30);
	pq.push(10);
	pq.push(50);
	pq.push(20);
	check("top() = 50, элемент остаётся в очереди", pq.top() == 50 && pq.size() == 4);
	check("порядок извлечения: 50 30 20 10", pq.pop() == 50 && pq.pop() == 30 && pq.pop() == 20 && pq.pop() == 10);
	check("pop() из пустой -> исключение", throwsEx<underflow_error>([&] { pq.pop(); }));
	check("top() из пустой -> исключение", throwsEx<underflow_error>([&] { pq.top(); }));
 
	PriorityQueue<int> bigPq;
	for (int i = 0; i < 50; i++)
		bigPq.push((i * 37) % 101);
	bool sorted = true;
	int prev = bigPq.pop();
	while (!bigPq.isEmpty())
	{
		int cur = bigPq.pop();
		if (cur > prev)
			sorted = false;
		prev = cur;
	}
	check("50 элементов: извлекаются по убыванию", sorted);
 
	cout << "\nK наименьших элементов:" << endl;
	int arr[] = {7, 2, 9, 4, 1, 8, 3};
	int res[3];
	kSmallest(arr, 7, 3, res);
	cout << "Массив: 7 2 9 4 1 8 3, три наименьших: " << res[0] << " " << res[1] << " " << res[2] << endl;
	check("три наименьших = 1 2 3", res[0] == 1 && res[1] == 2 && res[2] == 3);
 
	int dup[] = {5, 1, 1, 5, 2};
	int res2[3];
	kSmallest(dup, 5, 3, res2);
	check("дубликаты {5,1,1,5,2}, k = 3 -> 1 1 2", res2[0] == 1 && res2[1] == 1 && res2[2] == 2);
	check("k > n -> исключение", throwsEx<invalid_argument>([&] { kSmallest(arr, 7, 8, res); }));
 
	cout << (failed == 0 ? "\nВсе проверки пройдены." : "\nЕсть непройденные проверки!") << endl;
	return failed == 0 ? 0 : 1;
}
```
 


 
## Анализ сложности
 
Здесь `n` — текущее количество элементов, `k` — число искомых элементов.
 
| Операция                                       | Сложность   | Пояснение                                                                           |
| ---------------------------------------------- | ----------- | ----------------------------------------------------------------------------------- |
| `Stack::push`                                  | O(1) аморт. | Запись на вершину; редкое удвоение массива стоит O(n)                               |
| `Stack::pop`, `top`                            | O(1)        | Обращение к элементу по индексу вершины                                             |
| `Queue::enqueue`                               | O(1) аморт. | Запись в кольцевой буфер; редкое удвоение стоит O(n)                                |
| `Queue::dequeue`, `front`                      | O(1)        | Сдвиг индекса начала по модулю                                                      |
| `Deque::push_front`, `push_back`               | O(1)        | Вставка узла у `head` или `tail`                                                    |
| `Deque::pop_front`, `pop_back`                 | O(1)        | Удаление узла; `prev` даёт доступ к предпоследнему узлу                             |
| `Deque::front`, `back`                         | O(1)        | Доступ через `head` и `tail`                                                        |
| `PriorityQueue::push`                          | O(log n)    | Вставка в конец и `heapifyUp` (высота кучи — log n)                                 |
| `PriorityQueue::pop`                           | O(log n)    | Замена корня последним элементом и `heapifyDown`                                    |
| `PriorityQueue::top`                           | O(1)        | Максимум всегда в корне                                                             |
| `isEmpty`, `size`                              | O(1)        | Проверка счётчика                                                                   |
| Деструктор                                     | O(1) / O(n) | O(1) для массивов, O(n) для списка (удаление всех узлов)                            |
| `evalRPN`                                      | O(n)        | Один проход по токенам, каждая операция со стеком — O(1)                            |
| `TwoStackQueue::enqueue`                       | O(1)        | `push` во входной стек                                                              |
| `TwoStackQueue::dequeue`, `front`              | O(1) аморт. | Каждый элемент переносится между стеками не более одного раза; худший случай — O(n) |
| `FixedDeque::push_*`, `pop_*`, `front`, `back` | O(1)        | Арифметика индексов по модулю ёмкости                                               |
| `kSmallest`                                    | O(n log k)  | `n` вставок/замен в куче размера не более `k`, затем `k` извлечений                 |
 
## Вывод
 
В ходе лабораторной работы были реализованы четыре линейные структуры данных: стек на динамическом массиве, очередь на кольцевом буфере, дек на двусвязном списке и приоритетная очередь на двоичной куче. Для каждой из них решена задача варианта 2: вычисление выражения в обратной польской записи, очередь на двух стеках, дек фиксированной ёмкости и поиск K наименьших элементов.
 
Стек удобен там, где нужен обратный порядок обработки (разбор выражений), очередь — для обработки в порядке поступления. Кольцевой буфер позволяет выполнять операции очереди и дека за O(1) без сдвига элементов, а двусвязный список обеспечивает O(1) на обоих концах без ограничения размера. Двоичная куча даёт приоритетной очереди сложность O(log n) для вставки и извлечения; на её основе задача K наименьших элементов решается за O(n log k).
 
Ошибки обрабатываются исключениями, копирование запрещено для защиты от двойного освобождения памяти. Проверка с `AddressSanitizer` и `UndefinedBehaviorSanitizer` подтвердила отсутствие утечек памяти и неопределённого поведения.
 
## Ответы на контрольные вопросы
 
**1. В чём заключается принцип работы стека (LIFO)?**
 
Элементы добавляются и удаляются только с одного конца — вершины. Последний добавленный элемент извлекается первым («последним пришёл — первым ушёл»), как в стопке тарелок.
 
**2. В чём заключается принцип работы очереди (FIFO)?**
 
Элементы добавляются в конец очереди, а извлекаются из начала. Первый добавленный элемент извлекается первым («первым пришёл — первым ушёл»), как очередь в магазине.
 
**3. Чем дек отличается от обычной очереди?**
 
В обычной очереди добавление выполняется только в конец, а удаление — только из начала. В деке добавлять и удалять элементы можно с обоих концов (`push_front`, `push_back`, `pop_front`, `pop_back`), поэтому дек может работать и как стек, и как очередь.
 
**4. Что такое приоритетная очередь? Где она применяется?**
 
Это структура данных, в которой у каждого элемента есть приоритет, а извлекается элемент с наивысшим приоритетом. Применяется в планировщиках задач ОС, алгоритме Дейкстры, алгоритмах сжатия (код Хаффмана), симуляции событий, поиске K наибольших или наименьших элементов.
 
**5. Как реализовать стек на основе динамического массива?**
 
Хранятся указатель на массив, индекс вершины `topIndex` (изначально `-1`) и ёмкость. `push` увеличивает `topIndex` и записывает элемент, при заполнении массива выделяется массив вдвое большего размера и элементы копируются. `pop` возвращает `data[topIndex]` и уменьшает `topIndex`.
 
**6. Как реализовать очередь на основе кольцевого буфера?**
 
Хранятся массив, индекс начала `frontIndex`, количество элементов `count` и ёмкость. Элемент добавляется в позицию `(frontIndex + count) % capacity`, при удалении `frontIndex` сдвигается на `(frontIndex + 1) % capacity`. Когда буфер заполнен, массив расширяется, а элементы переписываются с индекса 0 в порядке очереди.
 
**7. Почему приоритетную очередь обычно реализуют на куче?**
 
Куча позволяет выполнять и вставку, и извлечение максимума за O(log n), а просмотр максимума — за O(1). Отсортированный массив даёт вставку за O(n), неотсортированный — извлечение за O(n). Куча также компактно хранится в обычном массиве без указателей.
 
**8. Какова сложность операций push и pop в стеке?**
 
Обе операции выполняются за O(1). Для `push` на динамическом массиве это амортизированная оценка, так как изредка происходит расширение массива за O(n).
 
**9. Какова сложность операций enqueue и dequeue в очереди?**
 
`enqueue` — O(1) амортизированно (на кольцевом буфере при расширении O(n), на связном списке строго O(1)), `dequeue` — O(1).
 
**10. Какова сложность операций в приоритетной очереди? Почему?**
 
`push` и `pop` — O(log n), `top` — O(1). После вставки или удаления элемент просеивается вверх или вниз по дереву, а высота двоичной кучи из `n` элементов равна `log n`. Максимальный элемент всегда находится в корне, поэтому `top` не требует поиска.
 
**11. Как проверить правильность расстановки скобок с помощью стека?**
 
Строка просматривается слева направо. Открывающая скобка кладётся в стек. При закрывающей скобке из стека извлекается верхний элемент, и он должен быть соответствующей открывающей скобкой, иначе расстановка неверна (также неверна, если стек пуст). В конце стек должен быть пуст.
 
**12. Как реализовать очередь на двух стеках? Какова сложность?**
 
Используются входной и выходной стеки. `enqueue` кладёт элемент во входной стек. `dequeue` берёт элемент из выходного стека, а если он пуст, то сначала переносит в него все элементы из входного (порядок при этом разворачивается и становится FIFO). `enqueue` — O(1), `dequeue` — O(1) амортизированно (худший случай — O(n) при переносе), так как каждый элемент переносится не более одного раза.
 
**13. Как реализовать дек на основе двусвязного списка?**
 
Хранятся указатели `head` и `tail`; каждый узел содержит данные, `prev` и `next`. `push_front`/`pop_front` работают с `head`, `push_back`/`pop_back` — с `tail`. Благодаря `prev` удаление из конца тоже выполняется за O(1). Нужно аккуратно обрабатывать случай единственного элемента, когда `head` и `tail` указывают на один узел.
 
**14. Как реализовать дек на основе кольцевого буфера?**
 
Хранятся массив, индекс первого элемента `frontIndex` и количество элементов `count`. `push_back` пишет в `(frontIndex + count) % capacity`, `push_front` сдвигает `frontIndex` назад: `(frontIndex - 1 + capacity) % capacity` — и пишет в него. `pop_front` сдвигает `frontIndex` вперёд, `pop_back` уменьшает `count`. При фиксированной ёмкости переполнение обрабатывается исключением.
 
**15. Как реализовать стек с поддержкой получения минимума за O(1)?**
 
Используется вспомогательный стек минимумов. При `push(x)` значение `x` добавляется в основной стек, а в стек минимумов — если он пуст или `x` не больше его вершины. При `pop` значение удаляется из стека минимумов, если оно равно его вершине. Текущий минимум всегда лежит на вершине вспомогательного стека. Другой вариант — хранить в каждом элементе пару «значение, минимум на момент добавления».
 
 