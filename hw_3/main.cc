// Во всех задачах из следующего списка следует написать структуру данных, обрабатывающую команды push* и pop*.
// Формат входных данных.
// В первой строке количество команд n. n ≤ 1000000.
// Каждая команда задаётся как 2 целых числа: a b.
// a = 1 - push front
// a = 2 - pop front
// a = 3 - push back
// a = 4 - pop back
// Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
// Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
// Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры данных, то ожидается “-1”. 
// Формат выходных данных.
// Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.

// 3_1. Реализовать очередь с динамическим зацикленным буфером.
// Требования: Очередь должна быть реализована в виде класса.

#include <iostream>
#include <cassert>

class DynamicBufferQueue {
public:
    DynamicBufferQueue() 
      : first_index_(0),
        last_index_(0),
        size_(2), 
        array_(new int[2]) {}
    ~DynamicBufferQueue() {
        delete[] array_;
    }

    int PopFront() {           
        if (first_index_ != last_index_) {  // проверка на существование обьектов в массиве 
            if (GetSize() < size_ / 2) {    // если необходимый размер меньше фактического в 2 раза, уменьшаем размер
                if (size_ / 2 >= 2)     // минимальная длинна массива будет равна 2
                    ChangeSize(size_ / 2);
            }
            int var = array_[first_index_];
            if (first_index_ + 1 != size_) {    // находится ли первый элемент на последнем месте в массиве
                first_index_++;
            } else {
                first_index_ = 0;
            }
            return var;
        } else {
            return -1;
        }
    }

    void PushBack(int b) {              
        if ((last_index_ + 1) % size_ == first_index_) {    // если индекс конца при увеличении будет указывать на начальный, увеличиваем массив в 2 раза 
            ChangeSize(size_ * 2);
        }
        if (last_index_ != size_) {     // если индекс конца не указывает за пределы массива
            array_[last_index_] = b;
            last_index_++;
        } else {        // если индекс конца указывает на конец массива
            array_[0] = b;
            last_index_ = 1;
        }

    }

    size_t GetSize() {                  // получение размера очереди 
        if (first_index_ <= last_index_) {
            return last_index_ - first_index_;
        } else {
            return size_ - first_index_ + last_index_;
        }
    }

private:
    int* array_;
    size_t first_index_;    // указывает на 1 эллемент
    size_t last_index_;     // указывает на следующий после последнего элемент
    size_t size_;           // размер динамического массива
    
    void ChangeSize(size_t new_size) {
        int* buffer_array = new int[new_size];
        if (first_index_ < last_index_) {           // если очередь не проходит через конец массива
            for (size_t i = 0; i < (last_index_ - first_index_); i ++) {
                buffer_array[i] = array_[i+ first_index_];
            }
            last_index_ -= first_index_;
            first_index_ = 0;
        } else if (first_index_ > last_index_) {    // если очередь проходит через конец массива
            for (size_t i = 0; i < (size_ - first_index_); i ++) {
                buffer_array[i] = array_[i+ first_index_];
            }
            for (size_t i = 0; i < last_index_; i ++) {
                buffer_array[i+(size_ - first_index_)] = array_[i];
            }
            last_index_ = size_ - first_index_ + last_index_;
            first_index_ = 0;
        }
        delete[] array_;
        array_ = buffer_array;
        size_ = new_size;
    }
};

bool CheckQueue(int n, int* array);

int main() {
    // ввод
    int n;
    std::cin >> n;
    int* array = new int[2 * n]; // на четных - a, на нечетных - b (из условия)
    for (int i = 0; i < n; i++) {
        std::cin >> array[2 * i];
        std::cin >> array[2 * i + 1];
    }
    // алгоритм
    bool result = CheckQueue(n, array);
    // вывод
    if (result) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }
	// очищение
	delete[] array;
    return 0;
}


bool CheckQueue(int n, int* array) {
    DynamicBufferQueue queue;
    for (int i = 0; i < n; i++) {
        if (array[2 * i] == 2) { // PopFront
            if (queue.PopFront() != array[2* i + 1]) {
                return false;
            }
        } else if (array[2 * i] == 3) { //PushBack
            queue.PushBack(array[2 * i + 1]);
        } else {    // некоректные данные
            return false;
        }
    }
    return true;
}