#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Route
{
private:
	string routeNumber;
	string startPoint;
	string endPoint;

public:
	Route(const string &num, const string &start, const string &end) : routeNumber(num), startPoint(start), endPoint(end)
	{
		cout << "[Создан] маршрут №" << routeNumber << " (" << startPoint << ' - ' << endPoint << ")" << endl;
	}

	~Route()
	{
		cout << "[Удалён] маршрут №" << routeNumber << endl;
	};

	string getInfo() const
	{
		return "№" + routeNumber + " (" + startPoint + " - " + endPoint + ")";
	}
};

class Bus
{
private:
	string model;
	string licensePlate;
	Route *route; // Указатель на маршрут (Агрегация)

	static int busCount;

public:
	Bus(const string &mod, const string &plate, Route *r = nullptr)
		: model(mod), licensePlate(plate), route(r)
	{
		busCount++;
		cout << "[Создан] Автобус: " << model << " [" << licensePlate << "]" << endl;
	}

	~Bus()
	{
		busCount--;
		cout << "[Удален] Автобус: " << model << " [" << licensePlate << "]" << endl;
	}

	// Сеттер для смены маршрута
	void setRoute(Route *r)
	{
		route = r;
	}

	void print() const
	{
		cout << "Автобус: " << model << " [" << licensePlate << "], ";
		// Проверка на nullptr
		if (route != nullptr)
		{
			cout << "назначен на маршрут " << route->getInfo() << endl;
		}
		else
		{
			cout << "не имеет маршрута" << endl;
		}
	}

	// Статический метод для получения количества автобусов
	static int getBusCount()
	{
		return busCount;
	}
};

int Bus::busCount = 0;

class Depot
{
private:
	string name;
	vector<Bus *> buses;

	Depot(const string &n) : name(n)
	{
		cout << "Депо открыто: " << name << endl;
	}

	static Depot *instance;

public:
	// Запрет копирования
	Depot(const Depot &) = delete;
	Depot &operator=(const Depot &) = delete;

	// Статический метод получения экземпляра
	static Depot *getInstance(const string &n = "Городское депо")
	{
		if (instance == nullptr)
		{
			instance = new Depot(n);
		}
		return instance;
	}

	void addBus(Bus *bus)
	{
		// Проверка на nullptr
		if (bus != nullptr)
		{
			buses.push_back(bus);
			cout << "Автобус добавлен в депо \"" << name << "\"" << endl;
		}
	}

	void print() const
	{
		cout << "\n--- Депо \"" << name << "\" содержит " << buses.size() << " автобус(ов) ---" << endl;
		if (buses.empty())
		{
			cout << "Депо пусто." << endl;
		}
		else
		{
			for (const auto &bus : buses)
			{
				bus->print();
			}
		}
		cout << "--------------------------------------------------\n"
			 << endl;
	}

	~Depot()
	{
		cout << "Закрыто депо: " << name << " (Автобусы не удаляются - агрегация)" << endl;
	}
};

Depot *Depot::instance = nullptr;

int main()
{
	setlocale(LC_ALL, "ru");

	cout << "1. Создаем маршруты независимо от автобусов:" << endl;
	Route route1("101", "Центр", "Север");
	Route route2("205", "Центр", "Юг");
	cout << endl;

	cout << "2. Создаем автобусы:" << endl;
	Bus bus1("ЛиАЗ-5292", "А123ВС", &route1);
	Bus bus2("Волгабас", "В456ЕК", &route2);
	Bus bus3("ПАЗ-3205", "С789МН");

	cout << "Всего создано автобусов: " << Bus::getBusCount() << endl
		 << endl;

	cout << "3. Демонстрация паттерна Singleton:" << endl;
	Depot *depot1 = Depot::getInstance("Центральное");
	Depot *depot2 = Depot::getInstance("Запасное");

	if (depot1 == depot2)
	{
		cout << "-> Успех: depot1 и depot2 указывают на один и тот же объект!" << endl;
	}
	cout << endl;

	cout << "4. Добавляем автобусы в депо:" << endl;
	depot1->addBus(&bus1);
	depot1->addBus(&bus2);
	depot1->addBus(&bus3);
	depot1->print();

	cout << "5. Проверка граничных случаев:" << endl;
	depot1->addBus(nullptr);
	cout << endl;

	cout << "6. Завершение программы:" << endl;

	return 0;
}