//  4_2. Порядковые статистики. Дано число N и N строк. Каждая строка содержит команду добавления или удаления натуральных чисел, 
//  а также запрос на получение k-ой порядковой статистики. Команда добавления числа A задается положительным числом A, 
//  команда удаления числа A задается отрицательным числом “-A”. Запрос на получение k-ой порядковой статистики задается числом k

#include <iostream>

template<typename T, typename Comparator = std::less<T>>
class AVLTree {
    struct Node
    {
        Node(T const& data)
              : data(data),
                height(1),
                left(nullptr),
                right(nullptr) {}
        T data;
        size_t height;
        Node* left;
        Node* right;
    };
public:
    AVLTree(Comparator cmp = Comparator())
          : cmp_(cmp),
            root_(nullptr) {}
    ~AVLTree() {
        DestroyTree(root_);
    }

    void Add(T const& data) {
        root_ = AddInternal(root_, data);
    }
    void Delete(T const& data) {
        root_ = DeleteInternal(root_, data);
    }
    T kthStat(int const& k) {
        Node* node = root_;
        int k_tmp = k;
        size_t left_hight = GetCount(node->left);
        while (left_hight != k_tmp && node) {
            if (left_hight < k_tmp) {
                k_tmp = k_tmp - left_hight - 1;
                node = node->right;
            } else if (left_hight > k_tmp) {
                node = node->left;
            }
            left_hight = GetCount(node->left);
        }

        return node->data;
    }

private:
    Node* root_;
    Comparator cmp_;

    Node* AddInternal(Node* node, T const& data) {
        if (!node) {
            return new Node(data);
        }
        if (cmp_(node->data, data)) {
            node->right = AddInternal(node->right, data);
        } else {
            node->left = AddInternal(node->left, data);
        }
        return DoBalance(node);
    }

    Node* DeleteInternal(Node* node, T const& data) {
        if(!node) {
            return nullptr;
        }

        if (cmp_(node->data, data)) {
            node->right = DeleteInternal(node->right, data);
        } else if (cmp_(data, node->data)) {
            node->left = DeleteInternal(node->left, data);
        } else {
            Node* left = node->left;
            Node* right = node->right;

            delete node;

            if (!right) {
                return left;
            }

            Node* min = FindMin(right);
            min->right = RemoveMin(right);
            min->left = left;
            
            return DoBalance(min);
        }
        return DoBalance(node);
    }

	size_t GetCount(Node* node) {
        if (node) {
            return GetCount(node->left) + GetCount(node->right) + 1;
        }
        return 0;
    }

    Node* FindMin(Node* node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    Node* RemoveMin(Node* node) {
        if (!node->left) {
            return node->right;
        }
        node->left = RemoveMin(node->left);
        return DoBalance(node);
    }

    size_t GetHight(Node* node) const { return node ? node->height : 0; }
    
    void FixHeight(Node* node) {
        node->height = (cmp_(GetHight(node->right), GetHight(node->left)) ? GetHight(node->left) : GetHight(node->right)) + 1;
    }

    Node* RotateLeft(Node* node) {
        Node* tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;
        FixHeight(node);
        FixHeight(tmp);
        return tmp;
    }

    Node* RotateRight(Node* node) {
        Node* tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;
        FixHeight(node);
        FixHeight(tmp);
        return tmp;
    }

    int GetBalance(Node* node) const {
        return GetHight(node->right) - GetHight(node->left);
    }

    Node* DoBalance(Node* node) {
        FixHeight(node);

        switch (GetBalance(node))
        {
        case 2:
            if (GetBalance(node->right) < 0) {
                node->right = RotateRight(node->right);
            }
            return RotateLeft(node);
        case -2:
            if (GetBalance(node->left) > 0) {
                node->left = RotateLeft(node->left);
            }
            return RotateRight(node);
        default:
            return node;
        }
    }

    void DestroyTree(Node* node) {
        if (node) {
            DestroyTree(node->left);
            DestroyTree(node->right);
            delete node;
        }
    }
};

void run() {
    int count;
    std::cin >> count;
    AVLTree<unsigned int> tree;
    for (int i = 0; i < count; i++) {
        int n;
        int k;
        std::cin >> n >> k;
        if (n > 0) {
            tree.Add(n);
        } else {
            tree.Delete(std::abs(n));
        }
        std::cout << tree.kthStat(k) << " ";
    }
}

int main() {
    run();
    return 0;
}


/*    
    void prinngn() {
        PrintTree(root_, 0);
    }

    void PrintTree(Node* node, int l) {
        int i;
        if (node) {
            PrintTree(node->right, l + 1);
            for (i = 1; i <= l; i++) std::cout << "    "; {
                std::cout << "|" << node->data << "(" << node->height << ")" <<std::endl;
            }
            PrintTree(node->left, l + 1);
        }
    }

*/
