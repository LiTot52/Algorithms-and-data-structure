# Лабораторная работа №4
# Тема: Односвязный и двусвязный списки

**Студент:** Геграев Ислам Русланович  
**Группа:** ПИЖ-б-о-25-2  
**Вариант:** 2  
**Уровень:** Продвинутый  
**Технологии:** C++

## Содержание

- [Лабораторная работа №4](#лабораторная-работа-4)
- [Тема: Односвязный и двусвязный списки](#тема-односвязный-и-двусвязный-списки)
	- [Содержание](#содержание)
	- [Цель работы](#цель-работы)
	- [Теоретическое обоснование](#теоретическое-обоснование)
	- [Постановка задачи](#постановка-задачи)
	- [Листинг программы](#листинг-программы)
		- [singlylinkedlist.hpp](#singlylinkedlisthpp)
		- [doublylinkedlist.hpp](#doublylinkedlisthpp)
		- [main.cpp](#maincpp)
	- [Анализ сложности](#анализ-сложности)
	- [Вывод](#вывод)
	- [Ответы на контрольные вопросы](#ответы-на-контрольные-вопросы)


## Цель работы

1. Реализовать шаблонный класс `SinglyLinkedList<T>` — односвязный список.
2. Реализовать шаблонный класс `DoublyLinkedList<T>` — двусвязный список.
3. Освоить операции вставки, удаления, поиска и обхода элементов в списках.
4. Сравнить производительность и особенности использования односвязного и двусвязного списков.
5. Научиться правильно управлять памятью при работе со списками.

## Теоретическое обоснование

**Связный список** — это структура данных, элементы которой (узлы) не хранятся в памяти непрерывно. Каждый узел содержит данные и указатель или указатели на соседние узлы.

**Односвязный список** — структура, в которой каждый узел содержит данные и указатель `next` на следующий узел. Последний узел указывает на `nullptr`.

```text
head ──► [10] ──► [20] ──► [30] ──► nullptr
```

**Двусвязный список** — структура, в которой каждый узел содержит данные, указатель `next` на следующий узел и указатель `prev` на предыдущий узел. Благодаря этому список можно обходить в обоих направлениях.

```text
nullptr ◄── [10] ⇄ [20] ⇄ [30] ──► nullptr
             head              tail
```

**Основные компоненты списка:**

* `head` — указатель на первый узел списка.
* `tail` — указатель на последний узел списка.
* `count` — количество элементов списка.
* `next` — указатель на следующий узел.
* `prev` — указатель на предыдущий узел (в двусвязном списке).

**Сравнение динамического массива и списков:**

| Операция           | Динамический массив (`vector`) | Односвязный список | Двусвязный список |
| ------------------ | ------------------------------ | ------------------ | ----------------- |
| Доступ по индексу  | O(1)                           | O(n)               | O(n)              |
| Вставка в начало   | O(n)                           | O(1)               | O(1)              |
| Вставка в конец    | O(1) амортизированно           | O(1) с `tail`      | O(1) с `tail`     |
| Удаление из начала | O(n)                           | O(1)               | O(1)              |
| Удаление из конца  | O(1)                           | O(n)               | O(1)              |
| Поиск по значению  | O(n)                           | O(n)               | O(n)              |

**Управление памятью:** каждый узел создаётся динамически с помощью `new`. После удаления узла необходимо освободить выделенную память с помощью `delete`. Для освобождения всех узлов списка используется метод `clear()`, который также вызывается в деструкторе.

**Односвязный и двусвязный списки:** односвязный список использует меньше дополнительной памяти, поскольку каждый узел хранит один указатель. Двусвязный список хранит два указателя, но позволяет перемещаться как вперёд, так и назад, а также удобнее удалять узлы при наличии указателя на них.

## Постановка задачи

**Вариант 2**

**Продвинутый уровень:**

* Реализовать шаблонный класс `SinglyLinkedList<T>` с базовой функциональностью односвязного списка.
* Реализовать шаблонный класс `DoublyLinkedList<T>` с базовой функциональностью двусвязного списка.
* Реализовать полную функциональность обоих списков.
* Реализовать операторы сравнения `==` и `!=` для списков.

## Листинг программы

### singlylinkedlist.hpp

```cpp
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
```

### doublylinkedlist.hpp

```cpp
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
```

### main.cpp

```cpp
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
```

## Анализ сложности

| Операция                       | Сложность | Пояснение                                         |
| ------------------------------ | --------- | ------------------------------------------------- |
| Конструктор по умолчанию       | O(1)      | Инициализация указателей и счётчика               |
| Деструктор                     | O(n)      | Удаление всех узлов списка                        |
| `push_front`                   | O(1)      | Добавление узла в начало                          |
| `push_back`                    | O(1)      | Добавление узла в конец при наличии `tail`        |
| `pop_front`                    | O(1)      | Удаление первого узла                             |
| `pop_back` односвязного списка | O(n)      | Необходимо найти предпоследний узел               |
| `pop_back` двусвязного списка  | O(1)      | Переход к предыдущему узлу через `prev`           |
| `find`                         | O(n)      | Последовательный поиск элемента                   |
| `remove`                       | O(n)      | Поиск удаляемого элемента и его удаление          |
| `clear`                        | O(n)      | Последовательное удаление всех узлов              |
| `size`, `empty`                | O(1)      | Получение значения счётчика или проверка головы   |
| `print`                        | O(n)      | Обход всех узлов списка                           |
| `printReverse`                 | O(n)      | Обход двусвязного списка от хвоста к голове       |
| `operator==`, `operator!=`     | O(n)      | Сравнение размеров и последовательности элементов |

## Вывод

В ходе лабораторной работы были изучены односвязные и двусвязные списки, их устройство и особенности работы. Были рассмотрены операции добавления, удаления, поиска и обхода элементов, а также принципы управления динамической памятью.

Односвязный список позволяет эффективно добавлять и удалять элементы в начале, а двусвязный список дополнительно обеспечивает обход в обратном направлении и более эффективное удаление последнего элемента. Реализация операторов сравнения `==` и `!=` позволяет проверять равенство списков по их содержимому.

## Ответы на контрольные вопросы

**1. Чем связный список отличается от динамического массива?**

В динамическом массиве элементы хранятся в непрерывной области памяти, поэтому доступ по индексу выполняется за O(1). В связном списке элементы находятся в отдельных узлах, связанных указателями. Доступ к элементу требует последовательного обхода и занимает O(n).

**2. Какие операции в односвязном списке выполняются за O(1)?**

Вставка в начало (`push_front`), удаление из начала (`pop_front`), получение размера (`size`) и проверка пустоты (`empty`). Вставка в конец также выполняется за O(1), если хранится указатель `tail`.

**3. Почему удаление из конца односвязного списка требует O(n) времени?**

Потому что у узла нет указателя на предыдущий элемент. Чтобы удалить последний узел, необходимо пройти список от головы и найти предпоследний элемент.

**4. Какие преимущества даёт хранение указателя `tail` в односвязном списке?**

Указатель `tail` позволяет обращаться к последнему элементу напрямую и добавлять новые элементы в конец за O(1), не обходя весь список.

**5. Чем двусвязный список отличается от односвязного?**

В односвязном списке каждый узел содержит указатель только на следующий элемент (`next`). В двусвязном списке узел содержит два указателя: на следующий (`next`) и предыдущий (`prev`).

**6. Какие операции в двусвязном списке выполняются быстрее, чем в односвязном?**

Удаление последнего элемента выполняется за O(1), если хранится `tail`, поскольку можно перейти к предыдущему узлу через `prev`. Также двусвязный список позволяет обходить элементы в обратном направлении.

**7. Что такое «голова» (`head`) и «хвост» (`tail`) списка?**

`head` — указатель на первый узел списка. `tail` — указатель на последний узел списка.

**8. Как удалить узел из середины односвязного списка?**

Необходимо найти узел, предшествующий удаляемому, изменить его указатель `next`, чтобы он ссылался на следующий после удаляемого узел, а затем освободить память удаляемого узла.

**9. Как удалить узел из середины двусвязного списка? Почему это проще?**

Нужно изменить указатель `next` предыдущего узла и указатель `prev` следующего узла, чтобы они ссылались друг на друга. Это проще, потому что у удаляемого узла есть прямые указатели на оба соседних узла.

**10. Что произойдёт, если забыть обновить `tail` при удалении?**

Указатель `tail` будет ссылаться на удалённую область памяти. Это может привести к ошибкам при обращении к последнему элементу, повреждению памяти и неопределённому поведению программы.

**11. Как реализовать реверс односвязного списка?**

Нужно пройти список и для каждого узла развернуть указатель `next` в сторону предыдущего узла. Для этого используются три указателя: `prev`, `current` и `next`. После обхода указатель `head` устанавливается на бывший последний элемент.

**12. Как обнаружить цикл в связном списке?**

Можно использовать алгоритм Флойда («черепаха и заяц»): два указателя проходят список с разной скоростью. Если в списке есть цикл, указатели встретятся. Если быстрый указатель достигнет `nullptr`, цикла нет.

**13. В каких случаях стоит использовать список вместо массива?**

Список удобно использовать, когда требуется часто вставлять и удалять элементы в начале или в известных позициях, а также когда не нужен быстрый доступ по индексу и размер структуры заранее неизвестен.

**14. Какая дополнительная память требуется для каждого узла списка?**

В односвязном списке каждый узел хранит один указатель `next`. В двусвязном списке каждый узел хранит два указателя: `next` и `prev`. Помимо этого, узел содержит сами данные.

**15. Почему доступ по индексу в списке имеет сложность O(n)?**

Потому что список не поддерживает прямой доступ к элементу по индексу. Чтобы получить нужный элемент, необходимо последовательно пройти узлы от начала списка до требуемой позиции.
