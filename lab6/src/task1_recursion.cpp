// Лабораторная №6, часть 1, вариант 2
// Задачи: факториал, числа Фибоначчи, количество цифр, бинарный поиск (все рекурсивно)
#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;

// ---------- Задача 1. Факториал ----------
long long factorial(int n) {
    if (n <= 1) return 1;            // базовый случай
    return n * factorial(n - 1);     // шаг рекурсии
}

long long factorialIter(int n) {     // итеративная версия для сравнения
    long long result = 1;
    for (int i = 2; i <= n; i++) result *= i;
    return result;
}

// ---------- Задача 2. Числа Фибоначчи ----------
long long fibRecursive(int n) {      // сложность O(2^n)
    if (n <= 1) return n;            // базовый случай
    return fibRecursive(n - 1) + fibRecursive(n - 2);
}

long long fibIterative(int n) {      // сложность O(n)
    if (n <= 1) return n;
    long long a = 0, b = 1;
    for (int i = 2; i <= n; i++) {
        long long c = a + b;
        a = b;
        b = c;
    }
    return b;
}

// ---------- Задача 3. Количество цифр числа ----------
int countDigits(long long n) {
    if (n < 0) n = -n;               // работаем с модулем
    if (n < 10) return 1;            // базовый случай: одна цифра
    return 1 + countDigits(n / 10);  // отбрасываем последнюю цифру
}

// ---------- Задача 4. Бинарный поиск (массив должен быть отсортирован) ----------
// Возвращает индекс элемента или -1, если не найден
int binarySearch(int arr[], int left, int right, int key) {
    if (left > right) return -1;                 // базовый случай: не найден
    int mid = left + (right - left) / 2;
    if (arr[mid] == key) return mid;             // базовый случай: найден
    if (arr[mid] > key) return binarySearch(arr, left, mid - 1, key);
    return binarySearch(arr, mid + 1, right, key);
}

int main() {
    // Задача 1
    cout << "=== Задача 1. Факториал ===" << endl;
    int n = 10;
    cout << n << "! (рекурсия)  = " << factorial(n) << endl;
    cout << n << "! (итерация) = " << factorialIter(n) << endl;

    // Задача 2
    cout << "\n=== Задача 2. Числа Фибоначчи ===" << endl;
    for (int i = 0; i <= 10; i++) cout << fibRecursive(i) << " ";
    cout << endl;

    int fn = 35;
    auto t1 = high_resolution_clock::now();
    long long r1 = fibRecursive(fn);
    auto t2 = high_resolution_clock::now();
    long long r2 = fibIterative(fn);
    auto t3 = high_resolution_clock::now();
    cout << "fib(" << fn << ") рекурсия: " << r1 << ", время "
         << duration_cast<milliseconds>(t2 - t1).count() << " мс" << endl;
    cout << "fib(" << fn << ") итерация: " << r2 << ", время "
         << duration_cast<microseconds>(t3 - t2).count() << " мкс" << endl;

    // Задача 3
    cout << "\n=== Задача 3. Количество цифр ===" << endl;
    long long numbers[] = {0, 7, 123, 98765, 1234567890};
    for (long long x : numbers)
        cout << x << " -> " << countDigits(x) << " цифр(ы)" << endl;

    // Задача 4
    cout << "\n=== Задача 4. Бинарный поиск ===" << endl;
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int size = sizeof(arr) / sizeof(arr[0]);
    int keys[] = {7, 19, 1, 4};
    for (int key : keys) {
        int idx = binarySearch(arr, 0, size - 1, key);
        if (idx != -1) cout << "Элемент " << key << " найден, индекс " << idx << endl;
        else cout << "Элемент " << key << " не найден" << endl;
    }
    return 0;
}
