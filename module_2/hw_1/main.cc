// Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв.
// Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
// Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
// Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.
// 1_1. Для разрешения коллизий используйте квадратичное пробирование. i-ая проба
// g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.

#include <iostream>
#include <string>
#include <vector>

#define A   43
#define InitialSize 8
#define LoadFactor 0.75
enum States { EMPTY, FILLED, DELETED };

// Хеш-функция строки
class StringHasher {    
public:    
    size_t operator()(std::string const& str) {
        size_t hash = 0;
        for (size_t i = 0; i < str.size(); i++) {
            hash = hash * A + str[i];
        }
        return hash;
    }
};

template<typename T>
struct HashTableNode {
    T data;
    States state;

    HashTableNode()
        : state(EMPTY) {}
        
    HashTableNode (std::string const& data)
        : data(data),
            state(FILLED) {} 
};

// Хеш-таблица
template<typename T, typename Hasher>
class HashTable {
public:
    HashTable()
          : table_(InitialSize),
            keys_count_(0) {}
    ~HashTable() = default;

    // Проверка принадлежности строки множеству
    bool Has(T const& key) {
        size_t hash = hasher_(key) % table_.size();
        for (size_t i = 0; i < table_.size(); i++) {
            auto node = &table_[hash];
            switch (node->state) {
            case FILLED:
                if (node->data == key) {
                    return true;
                }
                break;
            case EMPTY:
                return false;
            default:
                break;
            }
            hash = (hash + i) % table_.size();
        }
        return false;
    }

    // Добавление строки в множество
    bool Add(T const& key) {
        if (keys_count_ >= LoadFactor * table_.size()) {
            Rehashing();
        }

        size_t hash = hasher_(key) % table_.size();
        for (size_t i = 0; i < table_.size(); i++) {
            auto node = &table_[hash];
            switch (node->state) {
            case FILLED:
                if (node->data == key) {
                    return false;
                }
                break;
            case DELETED:
                node->state = FILLED;
                node->data = key;
                keys_count_++;
                return true;
            case EMPTY:
                node->state = FILLED;
                node->data = key;
                keys_count_++;
                return true;
            default:
                break;
            }
            hash = (hash + i) % table_.size();
        }
        return false;
    }

    // Удаление строки из множества
    bool Delete(T const& key) {
        size_t hash = hasher_(key) % table_.size();
        for (size_t i = 0; i < table_.size(); i++) {
            auto node = &table_[hash];
            switch (node->state) {
            case FILLED:
                if (node->data == key) {
                    node->state = DELETED;
                    keys_count_--;
                    return true;
                }
                break;
            case EMPTY:
                return false;
            default:
                break;
            }
            hash = (hash + i) % table_.size();
        }
        return false;
    }

    void print() {
        for (auto node : table_) {
            switch (node.state)
            {
            case FILLED:
                std::cout << node.data << " ";
                break;
            case DELETED:
                std::cout << "DEL ";
                break;
            case EMPTY:
                std::cout << "EMP ";
                break;
            
            default:
                break;
            }
        }
        std::cout << "count: " << keys_count_ <<std::endl;
    }

private:
    // Перехеширование
    void Rehashing() {
        
        size_t new_size = table_.size() * 2;
        std::vector<HashTableNode<T>> old_table = std::move(table_);
        std::vector<HashTableNode<T>> new_table(new_size);
        table_ = std::move(new_table);
        size_t new_count = 0;
        for (auto node : old_table) {
            if (node.state == FILLED) {
                new_count++;
                size_t hash = hasher_(node.data) % new_size;
                size_t j = 0;
                while (table_[hash].state == FILLED && j < new_size) {
                    j++;
                    hash = (hash + j) % new_size;
                }
                table_[hash] = node;
            }
        }
        keys_count_ = new_count;
    }

    std::vector<HashTableNode<T>> table_;
    
    size_t keys_count_;

    Hasher hasher_;
};

void run() {
    HashTable<std::string, StringHasher> hash_table;
    char operation;
    std::string key;

    while (std::cin >> operation >> key) {
        switch (operation) {
        case '+':
            std::cout << (hash_table.Add(key) ? "OK" : "FAIL") << std::endl;
            break;
        case '-':
            std::cout << (hash_table.Delete(key) ? "OK" : "FAIL") << std::endl;
            break;
        case '?':
            std::cout << (hash_table.Has(key) ? "OK" : "FAIL") << std::endl;
            break;
        default:
            break;
        }
        hash_table.print();
    }
}

int main() {
    run();
    return 0;
}
