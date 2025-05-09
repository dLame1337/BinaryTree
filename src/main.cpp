#include <iostream>
#include <initializer_list>
#include <utility>
#include <queue>

class BinaryTree
{
    struct Node
    {
        int key;
        int value;
        Node* left;
        Node* right;

        Node(int key, int value)
        {
            this->key = key;
            this->value = value;
            left = nullptr;
            right = nullptr;
        }
    };

public:
    BinaryTree() = default;

    BinaryTree(const BinaryTree& other)
    {
        if (this != &other)
        {
            m_size = other.m_size;
            m_root = copyTree(other.m_root);
        }
    }

    BinaryTree(BinaryTree&& other)
    {
        if (this != &other)
        {
            m_root = other.m_root;
            m_size = other.m_size;
            other.m_root = nullptr;
            other.m_size = 0;
        }
    }

    BinaryTree& operator=(const BinaryTree& other)
    {
        if (this != &other)
        {
            clear();
            m_size = other.m_size;
            m_root = copyTree(other.m_root);
        }
        return *this;
    }

    BinaryTree& operator=(BinaryTree&& other)
    {
        if (this != &other)
        {
            m_size = other.m_size;
            m_root = other.m_root;

            other.m_size = 0;
            other.m_root = nullptr;
        }
        return *this;
    }

    BinaryTree(std::initializer_list<std::pair<int, int>> list)
    {
        for(const auto& [key, value] : list)
            insert(key, value);
    }

    ~BinaryTree() { clear(); }

    void printTree()
    {
        std::cout << "--- PRINT TREE ---" << std::endl;

        if (m_root)
        {
            auto callback = [](Node *node)
            {
                std::cout << "Key: " << node->key << std::endl;
                std::cout << "Value: " << node->value << std::endl;
            };
            std::cout << "\n--- INORDER ---" << std::endl;
            inOrder(m_root, callback);
            std::cout << "\n--- PREORDER ---" << std::endl;
            preOrder(m_root, callback);
            std::cout << "\n--- POSTORDER ---" << std::endl;
            postOrder(m_root, callback);
            std::cout << "\n--- LEVELORDER ---" << std::endl;
            levelOrder(m_root, callback);
        }
    }

    int min()
    {
        if (!m_root)
            return int();

        return getMinNode(m_root)->key;
    }

    int max()
    {
        if (!m_root)
            return int();

        return getMaxNode(m_root)->key;
    }

    void insert(int key, int value)
    {
        if (m_root == nullptr)
        {
            m_root = new Node(key, value);
            ++m_size;
            return;
        }

        if (insert(m_root, key, value))
        {
            ++m_size;
        }
    }

    bool empty() const { return m_root == nullptr; }

    void remove(int key)
    {
        Node** node = findNode(key);
        if (!(*node))
            return; // didnt find

            remove(node);

        --m_size;
    }

    int* find(int key)
    {
        Node** node = findNode(key);
        if (!(*node))
            return nullptr; // didnt find
            else
                return &(*node)->value;
    }

    void clear()
    {
        if (m_root != nullptr)
            postOrder(m_root, [] (Node* node) { delete node; });

        m_root = nullptr;
        m_size = 0;
    }

    void inOrder(Node* node, void(*callback)(Node*))
    {
        if (node->left != nullptr)
            inOrder(node->left, callback);

        callback(node);

        if (node->right != nullptr)
            inOrder(node->right, callback);
    }

    void preOrder(Node* node, void(*callback)(Node*))
    {
        callback(node);

        if (node->left != nullptr)
            preOrder(node->left, callback);

        if (node->right != nullptr)
            preOrder(node->right, callback);
    }

    void postOrder(Node* node, void(*callback)(Node*))
    {
        if (node->left != nullptr)
            postOrder(node->left, callback);

        if (node->right != nullptr)
            postOrder(node->right, callback);

        callback(node);
    }

    void levelOrder(Node* node, void(*callback)(Node*))
    {
        std::queue<Node *> current_level;
        current_level.push(node);

        while(!current_level.empty())
        {
            Node*& curr_node = current_level.front();

            callback(curr_node);

            if (curr_node->left != nullptr)
                current_level.push(curr_node->left);

            if (curr_node->right != nullptr)
                current_level.push(curr_node->right);

            current_level.pop();
        }
    }

private:

    Node* copyTree(const Node* root) {
        if (!root) return nullptr;

        Node* new_node = new Node(root->key, root->value);
        new_node->left = copyTree(root->left);
        new_node->right = copyTree(root->right);
        return new_node;
    }

    Node* insert(Node* node, int key, int value)
    {
        if (node->key > key)
        {
            if (node->left == nullptr)
            {
                node->left = new Node(key, value);
                return node->left;
            }
            return insert(node->left, key, value);
        }
        else if (node->key < key)
        {
            if (node->right == nullptr)
            {
                node->right = new Node(key, value);
                return node->right;
            }
            return insert(node->right, key, value);
        }
        else // node->key == key
        {
            node->value = value;
            return nullptr;
        }
    }

    void remove(Node** node)
    {
        Node* left = (*node)->left;
        Node* right = (*node)->right;
        delete *node;

        if (left == nullptr && right == nullptr)
        {
            *node = nullptr;
            return;
        }
        else if (left == nullptr)
        {
            *node = right;
            return;
        }
        else if (right == nullptr)
        {
            *node = left;
            return;
        }
        Node* min_right = getMinNode(right);
        min_right->left = left->right;
        left->right = right;
        *node = left;
    }

    Node** findNode(int key)
    {
        Node** ref = &m_root;
        Node* curr = m_root;

        while (curr != nullptr)
        {
            if (curr->key > key)
            {
                ref = &curr->left;
                curr = curr->left;
                continue;
            }
            else if (curr->key < key)
            {
                ref = &curr->right;
                curr = curr->right;
                continue;
            }
            break;
        }

        return ref;
    }

    Node* getMinNode(Node* node)
    {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    Node* getMaxNode(Node* node)
    {
        while (node->right != nullptr)
            node = node->right;
        return node;
    }

private:
    Node* m_root = nullptr;
    size_t m_size = 0;

};

void test_binary_tree()
{
    BinaryTree tree({
        {10, 10},
        {5,  10},
        {2,  10},
        {7,  10},
        {15, 10},
        {20, 10}
    });

    tree.printTree();

    tree.remove(555);
    tree.remove(5);
    tree.remove(2);
    tree.remove(7);
    tree.printTree();

    tree.clear();
    tree.printTree();

    tree.insert(1, 10);
    tree.insert(55, 10);
    tree.insert(-23, 10);
    tree.printTree();

    std::cout << "Min: " << tree.min() << std::endl;
    std::cout << "Max: " << tree.max() << std::endl;
}

int main()
{
    test_binary_tree();
    return 0;
}
