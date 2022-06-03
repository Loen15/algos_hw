// Задача 3. B-дерево (4 балла)  

// Постройте B-дерево минимального порядка t и выведите его по слоям.  
// В качестве ключа используются числа, лежащие в диапазоне 0..2^32 -1

#include <iostream>
#include <vector>

template<typename T, typename Comparator = std::less<T>>
class Btree {
    struct Node {
        Node(bool leaf)
              : leaf(leaf) {}

        ~Node() {
            for (Node* child : children) {
                delete child;
            }
        }
        std::vector<T> keys;
        bool leaf;
        std::vector<Node*> children;
    };

public:
    Btree(size_t min_degree, Comparator cmp = Comparator()) 
          : t_(min_degree),
            root_(nullptr),
            cmp_(cmp) {
                 if (min_degree < 2)
                    throw std::invalid_argument("min degree must be >= 2");
            }
    ~Btree() {
        if (root_)
            delete root_;
    }

    void Insert(T const& key) {
        if (!root_) {
            root_ = new Node(true);
        }

        if (IsNodeFull(root_)) {
            Node* new_root = new Node(false);
            new_root->children.push_back(root_);
            root_ = new_root;
            SplitChild(root_, 0);
        }

        InsertNonFull(root_, key);
    }

    void DebugPrint() {
        DebuqPrint(root_, 0);
    }
private:
    Node* root_;
    size_t t_;
    Comparator cmp_;

    bool IsNodeFull(Node* node) {
        return node->keys.size() == 2 * t_ - 1;
    }

    void InsertNonFull(Node* node, T const& key) {
        size_t pos = node->keys.size() - 1;
        if (node->leaf) {
            node->keys.resize(node->keys.size() + 1);
            while (pos >= 0 && cmp_(key, node->keys[pos])) {
                node->keys[pos + 1] = node->keys[pos];
                pos--;
            }
            node->keys[pos + 1] = key;
        } else {
            while (pos >= 0 && cmp_(key, node->keys[pos])) {
                pos--;
            }
            if (IsNodeFull(node->children[pos + 1])) {
                SplitChild(node, pos + 1);
                if (cmp_(key, node->keys[pos + 1])) {
                    pos++;
                }
            }

        InsertNonFull(node->children[pos + 1], key);
        }
    }

    void DebuqPrint (Node* node, int indent) {
        std::cout << std::string(indent,' ');
        std::cout << "keys: [";
        for (auto it = node->keys.begin(); it != node->keys.end(); it++) {
            std::cout << (*it);
            if (it + 1 != node->keys.end())
                std::cout << ", ";
        }
        std::cout << "]" << std::endl;
        for (auto child : node->children) {
            DebuqPrint(child, indent + 4);
        }
    }
    void SplitChild(Node* node, size_t index) {
        Node* y = node->children[index];
        Node* z = new Node(y->leaf);
        std::cout << "1 split" << std::endl;
        for (size_t j = 0; j < t_ - 1; j++) {
            z->keys.push_back(y->keys[j + t_]);
        }
        std::cout << "2 split" << std::endl;
        if (!y->leaf) {
            for (size_t j = 0; j < t_; j++) {
                z->children.push_back(y->children[j + t_]);
            }
            y->children.resize(t_ - 1);
        }
        std::cout << "3 split" << std::endl;
        node->children.push_back(node->children[node->children.size() - 1]);
        for(size_t j = node->children.size() - 1; j > index + 1; j--) {
            node->children[j] = node->children[j - 1];
        }
        node->children[index + 1] = z;

        std::cout << "4 split" << std::endl;
        node->keys.resize(node->keys.size() + 1);
        std::cout << "4.5 split" << std::endl;
        
        for (size_t j = node->keys.size() - 1; j > index; --j) {
            node->keys[j] = node->keys[j - 1];
        }
        std::cout << "5 split" << std::endl;
        node->keys[index] = y->keys[t_ - 1];
        
        y->children.resize(t_ - 1);
        std::cout << "6 split" << std::endl;
        
    }
};

void run() {
    size_t t = 0;
    std::cin >> t;
    Btree<unsigned int> b_tree(t);
    unsigned int elems;
  while (std::cin >> elems) {
    b_tree.Insert(elems);
  }
  b_tree.DebugPrint();
}

int main() {
    run();
    return 0;
}