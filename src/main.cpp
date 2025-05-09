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
            inorder(m_root, callback);
            std::cout << "\n--- PREORDER ---" << std::endl;
            preorder(m_root, callback);
            std::cout << "\n--- POSTORDER ---" << std::endl;
            postorder(m_root, callback);
            std::cout << "\n--- LEVELORDER ---" << std::endl;
            levelorders(m_root, callback);
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

    void clear()
    {
        if (m_root != nullptr)
            postorder(m_root, [] (Node* node) { delete node; });

        m_root = nullptr;
        m_size = 0;
    }

    void inorder(Node* node, void(*callback)(Node*))
    {
        if (node->left != nullptr)
            inorder(node->left, callback);

        callback(node);

        if (node->right != nullptr)
            inorder(node->right, callback);
    }

    void preorder(Node* node, void(*callback)(Node*))
    {
        callback(node);

        if (node->left != nullptr)
            preorder(node->left, callback);

        if (node->right != nullptr)
            preorder(node->right, callback);
    }

    void postorder(Node* node, void(*callback)(Node*))
    {
        if (node->left != nullptr)
            postorder(node->left, callback);

        if (node->right != nullptr)
            postorder(node->right, callback);

        callback(node);
    }

    void levelorders(Node* node, void(*callback)(Node*))
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
