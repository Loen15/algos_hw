#include <iostream>
#include <exception>
#include <functional>

template <typename T>
class Array {
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
Array<T> Execute(int const& k, int* const& size, int ** const& arrays) {
    Heap<int> heap;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < size[i]; j++) {
            heap.Insert(arrays[i][j]);
        }
    }
    Array<T> result;
    while (!heap.IsEmpty()) {
        result.Insert(heap.ExtractMin());
    }
    return result;
}
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
    Array<int> result = Execute<int>(k, size,arrays);

    // вывод алгоритма
    result.PrintArr();
    // Heap<int> heap;
    // for (int i = 0; i < k; i++) {
    //     for (int j = 0; j < size[i]; j++) {
    //         heap.Insert(arrays[i][j]);
    //     }
    // }
    // if (!heap.IsEmpty())
    //     std::cout << heap.ExtractMin();
    // while (!heap.IsEmpty()) {
    //     std::cout << " " << heap.ExtractMin();
    // }
    // std::cout << std::endl;
    return 0;
}