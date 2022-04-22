// Дано множество целых чисел из [0..109] размера n.  
// Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:  
// 10% перцентиль  
// медиана  
// 90% перцентиль  
// Требования:  
// К дополнительной памяти: O(n).  
// Среднее время работы: O(n)  
// Должна быть отдельно выделенная функция partition.  
// Рекурсия запрещена.  
// Решение должно поддерживать передачу функции сравнения снаружи.  
// Формат ввода  
// Сначала вводится кол-во элементов массива n. После сам массив.  
// Формат вывода  
// Параметры множества в порядке:  
// 10% перцентиль  
// медиана  
// 90% перцентиль  
// 6_4. Реализуйте стратегию выбора опорного элемента “случайный элемент”.  
// Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.

#include <iostream>

template < typename T, typename Comparator = std::less<T>>
int Partition (T* arr, int l, int r, Comparator cmp = Comparator()) {
    // выбираем рандомный эл-мент, далее он будет на позиции l в массиве
    std::cout << "partition " << std::endl;
    if (l == r)
        return l;
    int pivot_pos = rand() % (r - l) + l;
    std::swap(arr[l], arr[pivot_pos]);
    int i = r;
    int j = r;
    // for (int f = 0; f < 10; f++) {
    while (true) {
        // std::cout << "partition2 with i; j " << i << "; " << j << std::endl;
    
        while (i > l && cmp(arr[l], arr[i])) {
            i--;
            j--;
            std::cout << i << ">" << l;
        }
        while (j > l && cmp(arr[j],arr[l])) {
            j--;
            std::cout << j << ">" << l;
        }
        if (j <= l) {
            std::cout << "exit from partition" << std::endl;
            std::swap(arr[l], arr[i]);
            return i;
        }
        std::swap(arr[i], arr[j]);
        i--;
        j--;
    }
}

template < typename T, typename Comparator = std::less<T>>
T kthStat(T* arr, int k, int n, Comparator cmp = Comparator()) {
    std::cout  << "kthstat arr with size: " << n << std::endl;
    // for (int i = 0; i < n; i++) {
    //     std::cout << "; ";
    // }
    int l = 0;
    int r = n-1;
    // инициализируем нвозможным значением, для захода в цикл
    int pivot_pos = -1;
    
    while (pivot_pos != k) {
        pivot_pos = Partition<T>(arr, l, r, cmp);
        std::cout << std::endl << "after partition arr: ";
        for (int i = 0; i < n; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
        if (pivot_pos > k) {
            r = pivot_pos - 1; 
        } else {
            l = pivot_pos + 1;
        }
    }
    
    return arr[pivot_pos];   
}

int main()
{
    // ввод
    int n;
    int* array;
    std::cin >> n;
    array = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> array[i];
    }
    std::cout << "readed" << std::endl;
    // алгоритм
    int* resultat = new int[3];
    resultat[0] = kthStat<int>(array,n * 1 / 10, n);
    resultat[1] = kthStat<int>(array,n * 5 / 10, n);
    resultat[2] = kthStat<int>(array,n * 9 / 10, n);
    
    // вывод
    std::cout << resultat[0] << std::endl;
    std::cout << resultat[1] << std::endl;
    std::cout << resultat[2] << std::endl;
    // чистка
    delete[] resultat;
    delete[] array;
    return 0;
}
