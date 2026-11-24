// Лабораторная №7: быстрая сортировка, сортировка слиянием, пирамидальная сортировка
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <algorithm>
using namespace std;
using namespace chrono;

// ---------- Быстрая сортировка ----------
int partition(int arr[], int low, int high)
{
    int pivot = arr[high]; // опорный элемент - последний
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ---------- Сортировка слиянием ----------
void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int *L = new int[n1];
    int *R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];

    delete[] L; // освобождаем память (нет утечек)
    delete[] R;
}

void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// ---------- Пирамидальная сортировка ----------
void heapify(int arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i); // построение кучи
    for (int i = n - 1; i > 0; i--)
    { // извлечение максимума
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Обёртки с одинаковой сигнатурой, чтобы удобно замерять время
void quickWrap(int a[], int n) { quickSort(a, 0, n - 1); }
void mergeWrap(int a[], int n) { mergeSort(a, 0, n - 1); }

bool isSorted(int arr[], int n)
{
    for (int i = 1; i < n; i++)
        if (arr[i - 1] > arr[i])
            return false;
    return true;
}

long long measureTime(void (*sortFunc)(int[], int), int arr[], int n)
{
    int *copy = new int[n];
    for (int i = 0; i < n; i++)
        copy[i] = arr[i];

    auto start = high_resolution_clock::now();
    sortFunc(copy, n);
    auto end = high_resolution_clock::now();

    if (!isSorted(copy, n))
        cout << "ОШИБКА: массив не отсортирован!" << endl;
    delete[] copy;
    return duration_cast<microseconds>(end - start).count();
}

int main()
{
    // Небольшой тест на корректность
    int test[] = {64, 34, 25, 12, 22, 11, 90, 5};
    int n = sizeof(test) / sizeof(test[0]);
    heapSort(test, n);
    cout << "Проверка (пирамидальная): ";
    for (int x : test)
        cout << x << " ";
    cout << endl
         << endl;

    // Сравнение на массивах разного размера
    int sizes[] = {1000, 10000, 50000, 100000};
    srand(42);
    cout << "Время сортировки (мкс), случайный массив:" << endl;
    cout << "N\t\tБыстрая\t\tСлиянием\tПирамидальная" << endl;
    for (int N : sizes)
    {
        int *arr = new int[N];
        for (int i = 0; i < N; i++)
            arr[i] = rand() % N;
        cout << N << "\t\t" << measureTime(quickWrap, arr, N)
             << "\t\t" << measureTime(mergeWrap, arr, N)
             << "\t\t" << measureTime(heapSort, arr, N) << endl;
        delete[] arr;
    }
    return 0;
}
