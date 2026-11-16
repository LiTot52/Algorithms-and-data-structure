#include <cassert>
#include <clocale>
#include <iostream>
#include <string>
#include <utility>
#include "structures.hpp"

//! Проверка: печатает результат и прерывает программу при ошибке
static void check(const std::string &name, bool cond)
{
	std::cout << (cond ? "[OK]   " : "[FAIL] ") << name << std::endl;
	assert(cond);
}

//! Возвращает true, если f() выбросила исключение типа Ex
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

static void printArray(const char *title, const int *a, int n)
{
	std::cout << title << "[ ";
	for (int i = 0; i < n; i++)
	{
		std::cout << a[i] << " ";
	}
	std::cout << "]" << std::endl;
}

static void testStack()
{
	std::cout << "\n===== 1. СТЕК + вычисление в обратной польской записи =====" << std::endl;

	Stack<int> s;
	s.push(1);
	s.push(2);
	s.push(3);
	std::cout << "Стек после push(1), push(2), push(3): ";
	s.print();
	check("pop() возвращает 3 (LIFO)", s.pop() == 3);
	check("top() возвращает 2 и не удаляет элемент", s.top() == 2 && s.size() == 2);

	Stack<int> small(2);
	for (int i = 0; i < 100; i++)
	{
		small.push(i);
	}
	check("расширение массива: size == 100, top == 99", small.size() == 100 && small.top() == 99);

	Stack<int> empty;
	check("pop() из пустого стека -> underflow_error", throwsEx<std::underflow_error>([&]
																					  { empty.pop(); }));
	check("top() из пустого стека -> underflow_error", throwsEx<std::underflow_error>([&]
																					  { empty.top(); }));

	Stack<int> copy(s);
	check("копия равна оригиналу (==)", copy == s);
	copy.push(7);
	check("после изменения копии стеки различны (!=)", copy != s);
	Stack<int> assigned;
	assigned = s;
	check("копирующее присваивание", assigned == s);
	Stack<int> moved(std::move(copy));
	check("перемещение: moved.size() == 3, исходный пуст", moved.size() == 3 && copy.isEmpty());

	std::cout << "\nОбратная польская запись:" << std::endl;
	std::cout << "\"3 4 + 5 *\" = " << evalRPN("3 4 + 5 *") << std::endl;
	check("3 4 + 5 * = 35", evalRPN("3 4 + 5 *") == 35.0);
	check("5 1 2 + 4 * + 3 - = 14", evalRPN("5 1 2 + 4 * + 3 -") == 14.0);
	check("10 2 / 3 - = 2", evalRPN("10 2 / 3 -") == 2.0);
	check("-5 3 + = -2 (отрицательное число)", evalRPN("-5 3 +") == -2.0);
	check("2.5 4 * = 10 (дробное число)", evalRPN("2.5 4 *") == 10.0);
	check("\"1 +\" -> invalid_argument", throwsEx<std::invalid_argument>([]
																		 { evalRPN("1 +"); }));
	check("\"4 0 /\" -> domain_error", throwsEx<std::domain_error>([]
																   { evalRPN("4 0 /"); }));
	check("\"\" -> invalid_argument", throwsEx<std::invalid_argument>([]
																	  { evalRPN(""); }));
	check("\"1 2\" -> invalid_argument", throwsEx<std::invalid_argument>([]
																		 { evalRPN("1 2"); }));
	check("\"1 a +\" -> invalid_argument", throwsEx<std::invalid_argument>([]
																		   { evalRPN("1 a +"); }));
}

static void testQueue()
{
	std::cout << "\n===== 2. ОЧЕРЕДЬ + очередь на двух стеках =====" << std::endl;

	Queue<int> q;
	q.enqueue(10);
	q.enqueue(20);
	q.enqueue(30);
	std::cout << "Очередь после enqueue(10), enqueue(20), enqueue(30): ";
	q.print();
	check("dequeue() возвращает 10 (FIFO)", q.dequeue() == 10);
	check("front() возвращает 20 и не удаляет элемент", q.front() == 20 && q.size() == 2);

	Queue<int> ring(3);
	ring.enqueue(1);
	ring.enqueue(2);
	ring.enqueue(3);
	ring.dequeue();
	ring.enqueue(4); // запись "по кругу"
	ring.enqueue(5); // расширение буфера
	check("кольцевой буфер и расширение: 2 3 4 5",
		  ring.dequeue() == 2 && ring.dequeue() == 3 && ring.dequeue() == 4 && ring.dequeue() == 5);

	Queue<int> empty;
	check("dequeue() из пустой очереди -> underflow_error", throwsEx<std::underflow_error>([&]
																						   { empty.dequeue(); }));
	check("front() из пустой очереди -> underflow_error", throwsEx<std::underflow_error>([&]
																						 { empty.front(); }));

	Queue<int> copy(q);
	check("копия равна оригиналу (==)", copy == q);
	copy.enqueue(99);
	check("после изменения копии очереди различны (!=)", copy != q);
	Queue<int> moved(std::move(copy));
	check("перемещение: moved.size() == 3, исходная пуста", moved.size() == 3 && copy.isEmpty());

	std::cout << "\nОчередь на двух стеках:" << std::endl;
	TwoStackQueue<int> tsq;
	tsq.enqueue(1);
	tsq.enqueue(2);
	tsq.enqueue(3);
	check("dequeue() == 1", tsq.dequeue() == 1);
	tsq.enqueue(4);
	check("front() == 2", tsq.front() == 2);
	check("порядок FIFO сохраняется: 2 3 4", tsq.dequeue() == 2 && tsq.dequeue() == 3 && tsq.dequeue() == 4);
	check("очередь пуста", tsq.isEmpty() && tsq.size() == 0);
	check("dequeue() из пустой -> underflow_error", throwsEx<std::underflow_error>([&]
																				   { tsq.dequeue(); }));
	check("front() из пустой -> underflow_error", throwsEx<std::underflow_error>([&]
																				 { tsq.front(); }));
}

static void testDeque()
{
	std::cout << "\n===== 3. ДЕК + дек фиксированной ёмкости =====" << std::endl;

	Deque<int> d;
	d.push_back(2);
	d.push_back(3);
	d.push_front(1);
	std::cout << "Дек после push_back(2), push_back(3), push_front(1): ";
	d.print();
	check("front() == 1, back() == 3", d.front() == 1 && d.back() == 3);
	check("pop_front() == 1", d.pop_front() == 1);
	check("pop_back() == 3", d.pop_back() == 3);
	check("pop_back() == 2, дек пуст", d.pop_back() == 2 && d.isEmpty());
	check("pop_front() из пустого дека -> underflow_error", throwsEx<std::underflow_error>([&]
																						   { d.pop_front(); }));
	check("pop_back() из пустого дека -> underflow_error", throwsEx<std::underflow_error>([&]
																						  { d.pop_back(); }));
	check("front() из пустого дека -> underflow_error", throwsEx<std::underflow_error>([&]
																					   { d.front(); }));
	check("back() из пустого дека -> underflow_error", throwsEx<std::underflow_error>([&]
																					  { d.back(); }));

	Deque<int> a;
	a.push_back(1);
	a.push_back(2);
	Deque<int> b(a);
	check("копия равна оригиналу (==)", a == b);
	b.push_front(0);
	check("после изменения копии деки различны (!=)", a != b);
	Deque<int> moved(std::move(b));
	check("перемещение: moved.size() == 3, исходный пуст", moved.size() == 3 && b.isEmpty());

	std::cout << "\nДек фиксированной ёмкости (3 элемента):" << std::endl;
	FixedDeque<int> fd(3);
	fd.push_back(1);
	fd.push_back(2);
	fd.push_front(0);
	std::cout << "После push_back(1), push_back(2), push_front(0): ";
	fd.print();
	check("дек заполнен: isFull() == true", fd.isFull() && fd.size() == 3);
	check("push_back() в полный дек -> overflow_error", throwsEx<std::overflow_error>([&]
																					  { fd.push_back(5); }));
	check("push_front() в полный дек -> overflow_error", throwsEx<std::overflow_error>([&]
																					   { fd.push_front(5); }));
	check("pop_front() == 0", fd.pop_front() == 0);
	check("pop_back() == 2", fd.pop_back() == 2);
	fd.push_front(9);
	fd.push_front(8); // индекс "переходит" через начало буфера
	std::cout << "После pop_front, pop_back, push_front(9), push_front(8): ";
	fd.print();
	check("кольцевой буфер: front == 8, back == 1", fd.front() == 8 && fd.back() == 1);
	check("порядок элементов: 8 9 1", fd.pop_front() == 8 && fd.pop_front() == 9 && fd.pop_front() == 1);
	check("pop_front() из пустого -> underflow_error", throwsEx<std::underflow_error>([&]
																					  { fd.pop_front(); }));
	check("pop_back() из пустого -> underflow_error", throwsEx<std::underflow_error>([&]
																					 { fd.pop_back(); }));
	check("ёмкость 0 -> invalid_argument", throwsEx<std::invalid_argument>([]
																		   { FixedDeque<int> bad(0); }));

	FixedDeque<int> f1(4);
	f1.push_back(1);
	f1.push_back(2);
	FixedDeque<int> f2(f1);
	check("копия равна оригиналу (==)", f1 == f2);
	f2.push_front(0);
	check("после изменения копии деки различны (!=)", f1 != f2);
	FixedDeque<int> fm(std::move(f2));
	check("перемещение: fm.size() == 3, исходный пуст", fm.size() == 3 && f2.isEmpty());
}

static void testPriorityQueue()
{
	std::cout << "\n===== 4. ПРИОРИТЕТНАЯ ОЧЕРЕДЬ + K наименьших элементов =====" << std::endl;

	PriorityQueue<int> pq;
	pq.push(30);
	pq.push(10);
	pq.push(50);
	pq.push(20);
	std::cout << "Куча после push(30), push(10), push(50), push(20): ";
	pq.print();
	check("top() == 50 и не удаляет элемент", pq.top() == 50 && pq.size() == 4);
	check("порядок извлечения: 50 30 20 10",
		  pq.pop() == 50 && pq.pop() == 30 && pq.pop() == 20 && pq.pop() == 10);
	check("очередь пуста", pq.isEmpty());
	check("pop() из пустой -> underflow_error", throwsEx<std::underflow_error>([&]
																			   { pq.pop(); }));
	check("top() из пустой -> underflow_error", throwsEx<std::underflow_error>([&]
																			   { pq.top(); }));

	PriorityQueue<int> big(2);
	for (int i = 0; i < 100; i++)
	{
		big.push((i * 37) % 101);
	}
	bool sorted = true;
	int prev = big.pop();
	while (!big.isEmpty())
	{
		int cur = big.pop();
		if (cur > prev)
		{
			sorted = false;
		}
		prev = cur;
	}
	check("100 элементов с расширением: извлечение по убыванию", sorted);

	PriorityQueue<int> p1;
	p1.push(5);
	p1.push(1);
	p1.push(3);
	PriorityQueue<int> p2(p1);
	check("копия равна оригиналу (==)", p1 == p2);
	p2.push(100);
	check("после изменения копии очереди различны (!=)", p1 != p2);
	PriorityQueue<int> moved(std::move(p2));
	check("перемещение: moved.top() == 100, исходная пуста", moved.top() == 100 && p2.isEmpty());

	std::cout << "\nK наименьших элементов:" << std::endl;
	int arr[] = {7, 2, 9, 4, 1, 8, 3};
	int res[3];
	printArray("Массив: ", arr, 7);
	kSmallest(arr, 7, 3, res);
	printArray("3 наименьших: ", res, 3);
	check("kSmallest({7,2,9,4,1,8,3}, k=3) = 1 2 3", res[0] == 1 && res[1] == 2 && res[2] == 3);

	int dup[] = {5, 1, 1, 5, 2};
	int res2[3];
	kSmallest(dup, 5, 3, res2);
	check("дубликаты {5,1,1,5,2}, k=3 -> 1 1 2", res2[0] == 1 && res2[1] == 1 && res2[2] == 2);

	int res3[7];
	kSmallest(arr, 7, 7, res3);
	check("k == n: массив отсортирован", res3[0] == 1 && res3[3] == 4 && res3[6] == 9);
	check("k > n -> invalid_argument", throwsEx<std::invalid_argument>([&]
																	   { kSmallest(arr, 7, 8, res3); }));
	check("k < 0 -> invalid_argument", throwsEx<std::invalid_argument>([&]
																	   { kSmallest(arr, 7, -1, res3); }));
}

int main()
{
	setlocale(LC_ALL, "ru");

	testStack();
	testQueue();
	testDeque();
	testPriorityQueue();

	std::cout << "\nВсе проверки пройдены." << std::endl;
	return 0;
}