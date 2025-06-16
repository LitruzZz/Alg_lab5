#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;

void showArray(const int arr[], int n) {
    for (int i = 0; i < n; ++i) cout << arr[i] << " ";
    cout << endl;
}

void exch(int& x, int& y) { int t = x; x = y; y = t; }

void shakerSortWithSteps(int a[], int n) {
    cout << "Шейкерне сортування\nПочатковий: ";
    showArray(a, n);
    int left = 1, right = n - 1, last = n - 1, phase = 1;
    do {
        cout << "Фаза " << phase++ << ":\nЗнизу вгору: ";
        for (int i = right; i > 0; --i) {
            if (a[i-1] > a[i]) {
                exch(a[i-1], a[i]);
                last = i;
            }
        }
        showArray(a, n);
        left = last + 1;
        if (left >= right) break;
        cout << "Згори вниз: ";
        for (int i = 1; i <= right; ++i) {
            if (a[i-1] > a[i]) {
                exch(a[i-1], a[i]);
                last = i;
            }
        }
        showArray(a, n);
        right = last - 1;
    } while (left < right);
}

void selectSort(int a[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int m = i;
        for (int j = i + 1; j < n; ++j)
            if (a[j] < a[m]) m = j;
        exch(a[i], a[m]);
    }
}

void bubbleSort(int a[], int n) {
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - i - 1; ++j)
            if (a[j] > a[j + 1])
                exch(a[j], a[j + 1]);
}

void shakerSort(int a[], int n) {
    int left = 1, right = n - 1, last = n - 1;
    do {
        for (int i = right; i > 0; --i)
            if (a[i-1] > a[i]) { exch(a[i-1], a[i]); last = i; }
        left = last + 1;
        for (int i = 1; i <= right; ++i)
            if (a[i-1] > a[i]) { exch(a[i-1], a[i]); last = i; }
        right = last - 1;
    } while (left < right);
}

// Сортування вставками
void insertSort(int a[], int n) {
    for (int i = 1; i < n; ++i) {
        int temp = a[i], j = i - 1;
        while (j >= 0 && a[j] > temp) { a[j + 1] = a[j]; --j; }
        a[j + 1] = temp;
    }
}

double measureSort(void (*sortFunc)(int[], int), int n) {
    int *a = new int[n];
    for (int i = 0; i < n; ++i) a[i] = rand() % 121 - 60;
    clock_t t1 = clock();
    sortFunc(a, n);
    clock_t t2 = clock();
    delete[] a;
    return (t2 - t1) * 1000.0 / CLOCKS_PER_SEC;
}

void compareSorts(const char* sortName, void (*sortFunc)(int[], int)) {
    cout << sortName << ":\n";
    int sizes[] = {300, 3000, 30000};
    for (int i = 0; i < 3; ++i)
        cout << "Для " << setw(5) << sizes[i] << " елементів: "
             << measureSort(sortFunc, sizes[i]) << " мс\n";
}

int main() {
    srand(time(0));
    cout << "Варіант 11, значення [-60; 60]\n";
    int d[10];
    for (int i = 0; i < 10; ++i) d[i] = rand() % 121 - 60;
    shakerSortWithSteps(d, 10);

    cout << "\nПорівняння алгоритмів\nРозміри: 300, 3000, 30000 елементів\n";
    compareSorts("Сортування вибором", selectSort);
    compareSorts("Бульбашкове сортування", bubbleSort);
    compareSorts("Шейкерне сортування", shakerSort);
    compareSorts("Сортування вставками", insertSort);
    return 0;
}
