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
#define INITIALSIZE 8
#define LOADFACTOR 0.75
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

// Хеш-таблица
template<typename T, typename Hasher>
class HashTable {
public:
    HashTable()
          : table_(INITIALSIZE),
            keys_count_(0) {}
    ~HashTable() = default;

    // Проверка принадлежности строки множеству
    bool Has(T const& key) {
        if (keys_count_ == 0) {
            return false;
        }
        size_t hash = hasher_(key) % table_.size();
        for (size_t i = 0; i < table_.size(); i++) {
            hash = (hash + i) % table_.size();
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
        }
        return false;
    }

    // Добавление строки в множество
    bool Add(T const& key) {
        if ((keys_count_ + 1) >= LOADFACTOR * table_.size()) {
            Rehashing();
        }

        size_t hash = hasher_(key) % table_.size();
        size_t del_index = table_.size();
        for (size_t i = 0; i < table_.size(); i++) {
            hash = (hash + i) % table_.size();
            auto node = &table_[hash];
            switch (node->state) {
            case FILLED:
                if (node->data == key) {
                    return false;
                }
                break;
            case DELETED:
                if (del_index == table_.size()) {
                    del_index = hash;
                }
                break;
            case EMPTY:
                if (del_index == table_.size()) {
                    node->state = FILLED;
                    node->data = key;
                } else {
                    table_[del_index].state = FILLED;
                    table_[del_index].data = key;
                }
                keys_count_++;
                return true;
            default:
                break;
            }
        }
        if (del_index != table_.size()) {
            table_[del_index].state = FILLED;
            table_[del_index].data = key;
            keys_count_++;
            return true;
        } else {
            return false;
        }
    }

    // Удаление строки из множества
    bool Delete(T const& key) {
        if (keys_count_ == 0) {
            return false;
        }
        size_t hash = hasher_(key) % table_.size();
        for (size_t i = 0; i < table_.size(); i++) {
            hash = (hash + i) % table_.size();
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
    struct HashTableNode {
        T data;
        States state;

        HashTableNode()
            : state(EMPTY) {}
            
        HashTableNode (std::string const& data)
            : data(data),
                state(FILLED) {} 
        HashTableNode& operator=(HashTableNode const& node) {
      		this->data = node.data;
      		this->state = node.state;
      		return *this;
    	}
    };
    // Перехеширование
    void Rehashing() {
        size_t new_size = table_.size() * 2;
        std::vector<HashTableNode> new_table(new_size);
        for (auto node : table_) {
            if (node.state == FILLED) {
                size_t hash = hasher_(node.data) % new_size;
                for (size_t i = 0; (i < new_size) && (new_table[hash].state == FILLED); i++) {
                    hash = (hash + i) % new_size;
                }
                new_table[hash] = node;
            }
        }
        table_ = std::move(new_table);
    }

    std::vector<HashTableNode> table_;
    
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
