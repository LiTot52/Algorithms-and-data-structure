#include <clocale>
#include <iostream>
#include "../include/structures.hpp"

// Возвращает true, если f() выбросила исключение типа Ex
template <typename Ex, typename F>
bool throwsEx(F f)
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
	std::cout << std::boolalpha;

	// ---------- 1. Стек (LIFO: последним пришёл, первым вышел) ----------
	std::cout << "--- Стек ---" << std::endl;
	Stack<int> s;
	s.push(1);
	s.push(2);
	s.push(3);
	std::cout << "top = " << s.top() << ", size = " << s.size() << std::endl;
	int x = s.pop();
	std::cout << "pop = " << x << std::endl;

	Stack<int> emptyStack;
	std::cout << "pop из пустого -> underflow_error: "
			  << throwsEx<std::underflow_error>([&]
												{ emptyStack.pop(); })
			  << std::endl;

	// Обратная польская запись
	std::cout << "\"3 4 + 5 *\"   = " << evalRPN("3 4 + 5 *") << std::endl;
	std::cout << "\"10 2 / 3 -\"  = " << evalRPN("10 2 / 3 -") << std::endl;
	std::cout << "\"4 0 /\" -> domain_error: "
			  << throwsEx<std::domain_error>([]
											 { evalRPN("4 0 /"); })
			  << std::endl;

	// ---------- 2. Очередь (FIFO: первым пришёл, первым вышел) ----------
	std::cout << "\n--- Очередь ---" << std::endl;
	Queue<int> q;
	q.enqueue(10);
	q.enqueue(20);
	q.enqueue(30);
	int first = q.dequeue();
	std::cout << "dequeue = " << first << ", front = " << q.front() << std::endl;

	// Очередь на двух стеках
	TwoStackQueue<int> tsq;
	tsq.enqueue(1);
	tsq.enqueue(2);
	tsq.enqueue(3);
	int t = tsq.dequeue();
	tsq.enqueue(4);
	std::cout << "TwoStackQueue: dequeue = " << t << ", остаток: ";
	while (!tsq.isEmpty())
		std::cout << tsq.dequeue() << " ";
	std::cout << std::endl;

	// ---------- 3. Дек (вставка и удаление с обоих концов) ----------
	std::cout << "\n--- Дек ---" << std::endl;
	Deque<int> d;
	d.push_back(2);
	d.push_back(3);
	d.push_front(1);
	std::cout << "front = " << d.front() << ", back = " << d.back() << std::endl;
	int df = d.pop_front();
	int db = d.pop_back();
	std::cout << "pop_front = " << df << ", pop_back = " << db
			  << ", size = " << d.size() << std::endl;

	// Дек фиксированной ёмкости
	FixedDeque<int> fd(3);
	fd.push_back(1);
	fd.push_back(2);
	fd.push_front(0);
	std::cout << "FixedDeque заполнен: " << fd.isFull() << std::endl;
	std::cout << "push_back в полный -> overflow_error: "
			  << throwsEx<std::overflow_error>([&]
											   { fd.push_back(5); })
			  << std::endl;

	// ---------- 4. Приоритетная очередь (первым выходит наибольший) ----------
	std::cout << "\n--- Приоритетная очередь ---" << std::endl;
	PriorityQueue<int> pq;
	pq.push(30);
	pq.push(10);
	pq.push(50);
	pq.push(20);
	std::cout << "Порядок извлечения: ";
	while (!pq.isEmpty())
		std::cout << pq.pop() << " ";
	std::cout << std::endl;

	// K наименьших элементов массива
	int arr[] = {7, 2, 9, 4, 1, 8, 3};
	int res[3];
	kSmallest(arr, 7, 3, res);
	std::cout << "3 наименьших из {7 2 9 4 1 8 3}: ";
	for (int i = 0; i < 3; i++)
		std::cout << res[i] << " ";
	std::cout << std::endl;

	return 0;
}