//Дан массив целых чисел А[0..n-1]. Известно, что на интервале [0, m] значения массива 
//строго возрастают, а на интервале [m, n-1] строго убывают. Найти m за O( log m ).
//2 ≤ n ≤ 10000.

#include <iostream>

int BinarySearch(int a[], size_t size);
int ExponentialSearch(int a[], size_t size);

int main() {
    // ввод
    size_t n;
    std::cin >> n;
    int* a = new int[n];
    for (size_t i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    // вывод алгоритма
    std::cout << ExponentialSearch(a, n) << std::endl;
    // очищение
    delete[] a;
    return 0;
}

int BinarySearch(int a[], size_t size) {
    size_t start_of_array = size / 2;
    a = a + start_of_array;
    size_t i = (size - start_of_array) / 2;
    size_t tmp = i;
    while (a[i - 1] > a [i] || a[i] < a [i + 1] && i < size) {
        if (tmp >= 2)
            tmp /= 2;
        if (a[i] < a [i + 1]) {
            i += tmp;
        } else {
            i -= tmp;
        }
        
    }
    return i+start_of_array;
}

int ExponentialSearch(int a[], size_t size) {
    size_t buf_size = 1;
    while (buf_size < size && a[buf_size - 1] < a[buf_size]) {
        buf_size *= 2;
    }
    buf_size = std::min(buf_size, size);
    int tmp = BinarySearch(a, buf_size);
    if (tmp != size) {
        return tmp;
    } else {
        return tmp - 1;
    }
}