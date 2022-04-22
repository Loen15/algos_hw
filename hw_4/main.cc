//Напишите программу, которая использует кучу для слияния K отсортированных массивов 
//суммарной длиной N.
//Требования:
//Время работы O(N * logK)
//Куча должна быть реализована в виде шаблонного класса.
//Решение должно поддерживать передачу функции сравнения снаружи.
//Куча должна быть динамической.
//Формат ввода
//Сначала вводится количество массивов K.
//Затем по очереди размер каждого массива и элементы массива.
//Каждый массив упорядочен по возрастанию.
//Формат вывода
//Итоговый отсортированный массив.

#include <iostream>
#include <exception>
#include <functional>

template <typename T>class Array {
public:
    Array () {}
    Array (size_t size) 
      : size_(size),
        elems_(new T[size_]) {}
    Array (size_t size, T const*  elems)
      : size_(size),
        elems_(new T[size_]) {
            for (size_t i = 0; i < size_; i++) {
                elems_[i] = elems[i];
            }
        }
    ~Array() { if (elems_) delete[] elems_; }

    T& operator[] (size_t i) {
        if (i >= size_) {
            throw std::out_of_range("index greater that size of Array");
        }
        return elems_[i];
    }

    void Insert(T const& elem) {
        T* buffer = new T[size_+1];
        for (size_t i = 0; i < size_; ++i) {
            buffer[i] = elems_[i];
        }
        buffer[size_] = elem;
        delete[] elems_;
        elems_ = buffer;
        size_++;
    }

    void Pop() {
        T* buffer = new T[size_-1];
        for (size_t i = 0; i < (size_-1); ++i) {
            buffer[i] = elems_[i];
        }
        delete[] elems_;
        elems_ = buffer;
        size_--;
    }
    size_t Size() const { return size_; }
    
    void PrintArr() {
        for (size_t i = 0; i < size_-1; i++) {
            std::cout << elems_[i] << " ";
        }
        std::cout << elems_[size_-1] << std::endl;
    }
private:
    size_t size_ = 0;
    T* elems_ = nullptr;
};

template <typename T>
class Heap {
public:
    Heap () : arr_(new Array<T>) {}
    Heap (const std::function<bool(T, T)>& compare)
      : arr_(new Array<T>),
        compare_(compare) {}
    ~Heap () {delete arr_; }

    // добавление элементов
    void Insert (T const& elem) {
        arr_->Insert(elem);
        SiftUp(arr_->Size()-1);
    }
    // извлечение минимума
    T ExtractMin() {
        if (IsEmpty()) {        
            throw std::out_of_range("Heap is empty");
        }
        T result = (*arr_)[0];
        (*arr_)[0] = (*arr_)[arr_->Size()-1];
        arr_->Pop();
        if (!IsEmpty()) {        
            SiftDown(0);
        }
        return result;;
    }

    bool IsEmpty() const { return arr_->Size() == 0; }
    size_t Size() const { return arr_->Size(); }

private:
    Array<T>* arr_;
    const std::function<bool(T, T)> compare_ = ([] (T const& left, T const& right)
        {
            return left < right;
        });
        
    void SiftDown(size_t i) {
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;
        size_t largest = i;
        if( left < arr_->Size() && compare_((*arr_)[left], (*arr_)[i]) )
            largest = left;
        if( right < arr_->Size() && compare_((*arr_)[right], (*arr_)[largest]) )
            largest = right;
        if (largest !=  i) {
            std::swap((*arr_)[i], (*arr_)[largest]);
            SiftDown(largest);
        }
    }
    void SiftUp(size_t i) {
        while (i > 0)
        {
            size_t parent = (i - 1) / 2;
            if (!compare_((*arr_)[i], (*arr_)[parent]))
                return;
            std::swap((*arr_)[i],(*arr_)[parent]);
            i = parent;
            
        }
        
    }
};

template <typename T>
class SupportingStruct {
public:
    SupportingStruct() {}
    SupportingStruct(T val, int index) : value_(val), index_(index) {}

    void SetValue(T const& value) { value_ = value; }
    void SetIndex(int const& index) { index_ = index; }
    T Value() const { return value_; }
    int Index() const { return index_; }

private:
    T value_;
    int index_;
};

Array<int> Execute(int const& k, int* const& size, int ** const& arrays) {
    SupportingStruct<int> buff; 
    Heap<SupportingStruct<int>> heap([] (SupportingStruct<int> const& left, SupportingStruct<int> const& right)
        {
            return left.Value() < right.Value();
        });
    int* index = new int[k];
    // добавляю по первому эллементу каждого массива в кучу 
    // и ицициализирую индексы началом массива 
    // время работы O(K)
    for (int i = 0; i < k; i++) {
        index[i] = 1;
        buff.SetValue(arrays[i][0]);
        buff.SetIndex(i);
        heap.Insert(buff);
    }
    Array<int> result;
    bool key = true;
    
    while (key) {
        // записываю минимальный элемент кучи в результат
        // вызывается N-k+1 раз время работы O(log(K))
        buff = heap.ExtractMin();
        result.Insert(buff.Value());
        
        // если в массиве есть еще числа
        // вызывается N-k раз время работы O(log(K))
        if (index[buff.Index()] < size[buff.Index()]) {
            buff.SetValue(arrays[buff.Index()][index[buff.Index()]]);
            heap.Insert(buff);
            index[buff.Index()]++;       
        }

        // если достигнут конец одного из массива 
        else {
            int i = 0;

            // вызывается K раз время работы O(1)
            while (index[i] >= size[i] && i < k) {
                i++;
            }
            
            // если есть массивы не достигшие конца
            // вызывается K-1 раз время работы O(log(K)) 
            if (i < k) {
                buff.SetValue(arrays[i][index[i]]);
                buff.SetIndex(i);
                heap.Insert(buff);
                index[i]++;
            }

            // если все массивы обработанны
            else {

                // вызывается 1 раз время работы O((K-1)*log(K))
                for (int i = 1; i < k; i++) {
                    buff = heap.ExtractMin();
                    result.Insert(buff.Value());
                }
                key = false;
            }
        }
    }
    return result;
}
// время работы Execute(): K + (N-K+1)log(K) + (N-K)log(K) + K + (K-1)*log(K) + (K-1)*log(K)=log(K) * (N-K+1+N-K+K-1+K-1)+ 2 * K =
// = (2*N -1) * log(K) + 2 * K ~ O(N * log(K))
int main() {
    // ввод
    int k;
    std::cin >> k;
    int* size = new int[k];
    int** arrays = new int*[k];
    for (int i = 0; i < k; i++) {
        std::cin >> size[i];
        arrays[i] = new int[size[i]];
        for (int j = 0; j < size[i]; j++) {
            std::cin >> arrays[i][j];
        }
    }
    
    // алгоритм
    Array<int> result = Execute(k, size,arrays);

    // вывод алгоритма
    result.PrintArr();

	for (int i = 0; i < k; i++) {
		delete[] arrays[i];
    }
	delete[] arrays;
    return 0;
}