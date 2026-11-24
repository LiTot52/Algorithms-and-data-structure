// Лабораторная №6, часть 2, вариант 2
// Пузырьковая, вставками, выбором. Сравнение на почти отсортированном массиве
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <algorithm>
using namespace std;
using namespace chrono;

// Пузырьковая сортировка (с оптимизацией: выход, если обменов не было)
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// Сортировка вставками
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Сортировка выбором
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) minIndex = j;
        }
        if (minIndex != i) swap(arr[i], arr[minIndex]);
    }
}

// Проверка, что массив отсортирован
bool isSorted(int arr[], int n) {
    for (int i = 1; i < n; i++)
        if (arr[i - 1] > arr[i]) return false;
    return true;
}

// Замер времени сортировки на копии массива (в микросекундах)
long long measureTime(void (*sortFunc)(int[], int), int arr[], int n) {
    int* copy = new int[n];
    for (int i = 0; i < n; i++) copy[i] = arr[i];

    auto start = high_resolution_clock::now();
    sortFunc(copy, n);
    auto end = high_resolution_clock::now();

    if (!isSorted(copy, n)) cout << "ОШИБКА: массив не отсортирован!" << endl;
    delete[] copy;
    return duration_cast<microseconds>(end - start).count();
}

int main() {
    const int N = 10000;
    int* arr = new int[N];
    srand(42);

    // Почти отсортированный массив: сначала по порядку, затем ~1% случайных обменов
    for (int i = 0; i < N; i++) arr[i] = i;
    for (int k = 0; k < N / 100; k++) swap(arr[rand() % N], arr[rand() % N]);

    cout << "Почти отсортированный массив (N = " << N << "):" << endl;
    cout << "Пузырьковая: " << measureTime(bubbleSort, arr, N) << " мкс" << endl;
    cout << "Вставками:   " << measureTime(insertionSort, arr, N) << " мкс" << endl;
    cout << "Выбором:     " << measureTime(selectionSort, arr, N) << " мкс" << endl;

    delete[] arr;
    return 0;
}
