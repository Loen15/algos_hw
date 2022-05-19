// Задача 2. Порядок обхода (4 балла)  
// Дано число N < 10^6 и последовательность целых чисел из [-231..231] длиной N.  
// Требуется построить бинарное дерево, заданное наивным порядком вставки.  
// Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.  
// Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.  
// 2_4. Выведите элементы в порядке level-order (по слоям, “в ширину”).

#include <iostream>
#include <queue>

template<typename T, typename Comparator = std::less<T>>
class Tree {
    struct Node {
    Node(T const& data)
        : value(data),
            left(nullptr),
            right(nullptr) {}
        T value;
        Node* left;
        Node* right;
    };
public:
    Tree(Comparator cmp = Comparator())
          : cmp_(cmp),
            root_(nullptr),
            size_(0) {}
    
    ~Tree() {
        auto for_delete = LevelOrder();
        while (!for_delete.empty()) {
            delete for_delete.front();
            for_delete.pop();
        }
    }

    void Add(T const& data) {
        if (root_ != nullptr) {
            Node* node = root_;
            Node* prev = nullptr;
            while (node != nullptr) {
                prev = node;
                if (cmp_(data, node->value)) {
                    node = node->left;
                } else {
                    node = node->right;
                }
            }
            node = new Node(data);
            size_++;
            if (cmp_(node->value, prev->value)) {
                prev->left = node;
            } else {
                prev->right = node;
            }
        } else {
            root_ = new Node(data);
        }
    }

    std::queue<Node*> LevelOrder() {
        std::queue<Node*> output;
        
        if (root_ == nullptr) {
            return output;
        }

        std::queue<Node*> q;
        q.push(root_);
        while (!q.empty()) {
            Node* node = q.front();
            q.pop();
            output.push(node);
            if (node->left != nullptr) {
                q.push(node->left);
            }
            if (node->right != nullptr) {
                q.push(node->right);
            }
        }
        return output;
    }
private:
    Node* root_;
    size_t size_;
    Comparator cmp_;
};

void run(std::queue<int> input) {
    Tree<int> tree;
    while (!input.empty()) {
        tree.Add(input.front());
        input.pop();
    }
    auto ouput = tree.LevelOrder();
    // вывод
    while (!ouput.empty()) {
        std::cout << ouput.front()->value << " ";
        ouput.pop();
    }
}

int main() {
    //ввод
    int n;
    std::cin >> n;
    std::queue<int> input;
    for (int i = 0; i < n; i++) {
        int tmp;
        std::cin >> tmp;
        input.push(tmp);
    }
    // алгоритм
    run(input);
    return 0;
}
