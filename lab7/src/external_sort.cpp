// Лабораторная №7, продвинутый уровень, вариант 2:
// сортировка слиянием для внешней сортировки (файлы)
//
// Идея: файл не помещается в память целиком, поэтому
//  1) читаем его кусками (chunk), каждый кусок сортируем в памяти и пишем во временный файл;
//  2) затем сливаем все временные файлы в один отсортированный (k-путевое слияние).
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <cstdio>
#include <cstdlib>
using namespace std;

// ---------- Сортировка слиянием в памяти ----------
void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right) temp[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    for (int idx = 0; idx < k; idx++) arr[left + idx] = temp[idx];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// ---------- Работа с файлами ----------

// Создаёт файл со случайными числами
void generateFile(const string& name, int count) {
    ofstream out(name);
    for (int i = 0; i < count; i++) out << rand() % 1000000 << "\n";
}

// Шаг 1: делит входной файл на отсортированные куски. Возвращает количество кусков.
int splitAndSort(const string& inputName, int chunkSize) {
    ifstream in(inputName);
    int chunks = 0;
    vector<int> buffer;
    int x;

    while (true) {
        buffer.clear();
        while ((int)buffer.size() < chunkSize && (in >> x)) buffer.push_back(x);
        if (buffer.empty()) break;

        mergeSort(buffer, 0, buffer.size() - 1);

        ofstream out("chunk_" + to_string(chunks) + ".txt");
        for (int v : buffer) out << v << "\n";
        chunks++;
    }
    return chunks;
}

// Элемент очереди: значение и номер файла, из которого оно прочитано
struct Item {
    int value;
    int file;
};
struct Compare {
    bool operator()(const Item& a, const Item& b) const { return a.value > b.value; }
};

// Шаг 2: сливает все куски в один выходной файл
void mergeChunks(int chunks, const string& outputName) {
    vector<ifstream> files(chunks);
    priority_queue<Item, vector<Item>, Compare> heap;   // берём минимальный из текущих

    for (int i = 0; i < chunks; i++) {
        files[i].open("chunk_" + to_string(i) + ".txt");
        int x;
        if (files[i] >> x) heap.push({x, i});
    }

    ofstream out(outputName);
    while (!heap.empty()) {
        Item cur = heap.top();
        heap.pop();
        out << cur.value << "\n";
        int x;
        if (files[cur.file] >> x) heap.push({x, cur.file});
    }

    for (int i = 0; i < chunks; i++) {
        files[i].close();
        remove(("chunk_" + to_string(i) + ".txt").c_str());   // удаляем временные файлы
    }
}

// Проверка, что результат отсортирован и содержит нужное количество чисел
bool checkFile(const string& name, int expectedCount) {
    ifstream in(name);
    int prev, x, count = 0;
    bool ok = true;
    while (in >> x) {
        if (count > 0 && x < prev) ok = false;
        prev = x;
        count++;
    }
    return ok && count == expectedCount;
}

int main() {
    const int TOTAL = 1000000;     // всего чисел в файле
    const int CHUNK = 100000;      // сколько чисел помещается в памяти за раз

    srand(42);
    cout << "Генерация файла numbers.txt (" << TOTAL << " чисел)..." << endl;
    generateFile("numbers.txt", TOTAL);

    cout << "Разбиение на отсортированные куски по " << CHUNK << " чисел..." << endl;
    int chunks = splitAndSort("numbers.txt", CHUNK);
    cout << "Получено кусков: " << chunks << endl;

    cout << "Слияние кусков в sorted.txt..." << endl;
    mergeChunks(chunks, "sorted.txt");

    if (checkFile("sorted.txt", TOTAL)) cout << "Готово: файл sorted.txt отсортирован верно." << endl;
    else cout << "ОШИБКА: результат неверный!" << endl;
    return 0;
}
