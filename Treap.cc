#include <iostream>
#include <random>
#include <stack>
using namespace std;

template <typename T>
class Treap
{
private:
    mt19937 gen;
    uniform_int_distribution<> distrib;

    class Node
    {
    private:
        T data_;
        int priority_;
        Node *left_;
        Node *right_;

    public:
        Node(const T &data, int priority)
            : data_(data), left_(nullptr), right_(nullptr), priority_(priority) {}

        T getData() const { return data_; }
        int getPriority() const { return priority_; }
        Node *getLeft() const { return left_; }
        Node *getRight() const { return right_; }

        void setLeft(Node *l) { left_ = l; }
        void setRight(Node *r) { right_ = r; }
    };

private:
    Node *root;
    unsigned int size_;

    bool empty() const { return root == nullptr; }

    Node *rotateRight(Node *y)
    {
        Node *x = y->getLeft();
        Node *z = x->getRight();

        x->setRight(y);
        y->setLeft(z);

        return x;
    }

    Node *rotateLeft(Node *y)
    {
        Node *x = y->getRight();
        Node *z = x->getLeft();

        x->setLeft(y);
        y->setRight(z);

        return x;
    }

    Node *insert(Node *root, const T &data)
    {
        if (root == nullptr)
        {
            return new Node(data, distrib(gen));
        }
        // Buscamos donde quedará el nuevo nodo.
        if (data < root->getData())
            root->setLeft(insert(root->getLeft(), data));
        else
            root->setRight(insert(root->getRight(), data));
        // Balanceamos.
        if (root->getLeft() != nullptr && root->getLeft()->getPriority() > root->getPriority())
            root = rotateRight(root);
        else if (root->getRight() != nullptr && root->getRight()->getPriority() > root->getPriority())
            root = rotateLeft(root);
        size_++;
        return root;
    }

    Node *remove(Node *node, const T &data)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        if (data < node->getData())
            node->setLeft(remove(node->getLeft(), data));
        else if (data > node->getData())
            node->setRight(remove(node->getRight(), data));
        else
        {
            // Caso 1: Nodo Hoja.
            if (node->getLeft() == nullptr && node->getRight() == nullptr)
            {
                delete node;
                return nullptr;
            }
            else if (node->getLeft() == nullptr || node->getRight() == nullptr)
            { // Caso 2: Un hijo.
                Node *temp = nullptr;
                if (node->getLeft() != nullptr)
                    temp = node->getLeft();
                else
                    temp = node->getRight();
                delete node;
                return temp;
            }
            else if (node->getLeft() != nullptr && node->getRight() != nullptr)
            { // Caso 3: Dos hijos.
                Node *temp = nullptr;
                if (node->getLeft()->getPriority() > node->getRight()->getPriority())
                {
                    node = rotateRight(node);
                    node->setRight(remove(node->getRight(), data));
                }
                else if (node->getRight()->getPriority() >= node->getLeft()->getPriority())
                {
                    node = rotateLeft(node);
                    node->setLeft(remove(node->getLeft(), data));
                }
            }
        }
        size_--;
        return node;
    }

    void printOrder(Node *node) const
    {
        if (node == nullptr)
            return;
        printOrder(node->getLeft());
        cout << "(" << node->getData() << ", " << node->getPriority() << ")" << " -> ";
        printOrder(node->getRight());
    }

    void PreOrder(Node *node) const
    {
        if (node == nullptr)
            return;
        cout << "(" << node->getData() << ", " << node->getPriority() << ")" << " -> ";
        PreOrder(node->getLeft());
        PreOrder(node->getRight());
    }

    void iterativePreorder(Node *node) const
    {
        if (node == nullptr)
            return;
        stack<Node *> st;
        st.push(node);
        while (!st.empty())
        {
            node = st.top();
            st.pop();
            cout << "(" << node->getData() << ", " << node->getPriority() << ")" << " -> ";
            if (node->getRight() != nullptr)
                st.push(node->getRight());
            if (node->getLeft() != nullptr)
                st.push(node->getLeft());
        }
    }

    void PostOrder(Node *node) const
    {
        if (node == nullptr)
            return;

        PostOrder(node->getLeft());
        PostOrder(node->getRight());

        cout << "(" << node->getData() << ", " << node->getPriority() << ")" << " -> ";
    }

    void iterativePostOrder(Node *node) const
    {
        if (node == nullptr)
            return;
        stack<Node *> st;
        Node *lastNodeVisited = nullptr;
        while (!st.empty() || node != nullptr)
        {
            if (node != nullptr)
            {
                st.push(node);
                node = node->getLeft();
            }
            else
            {
                Node *peekNode = st.top();
                if (peekNode->getRight() != nullptr && lastNodeVisited != peekNode->getRight())
                {
                    node = peekNode->getRight();
                }
                else
                {
                    cout << "(" << peekNode->getData() << ", " << peekNode->getPriority() << ")" << " -> ";
                    lastNodeVisited = st.top();
                    st.pop();
                }
            }
        }
    }

    int height(Node *node)
    {
        if (node == nullptr)
            return -1;
        int leftHeight = height(node->getLeft());
        int rightHeight = height(node->getRight());
        return 1 + max(leftHeight, rightHeight);
    }

public:
    Treap() : gen(random_device{}()), distrib(0, 100), root(nullptr) {}

    void insert(const T &data)
    {
        root = insert(root, data);
    }

    void printInOrder() const // left_SubTree->Root->right_SubTree.
    {
        if (empty())
            return;
        printOrder(root);
        cout << "nullptr" << endl;
    }

    void printPreOrder() const // Root->left_SubTree->right_SubTree.
    {
        if (empty())
            return;
        PreOrder(root);
        cout << "nullptr" << endl;
    }

    void IterativePreOrder() const
    {
        if (empty())
            return;
        iterativePreorder(root);
        cout << "nullptr" << endl;
    }

    void printPostOrder() const // left_SubTree->right_SubTree->Root.
    {
        if (empty())
            return;
        PostOrder(root);
        cout << "nullptr" << endl;
    }

    void printIterativePostOrder() const
    {
        if (empty())
            return;
        iterativePostOrder(root);
        cout << "nullptr" << endl;
    }

    int height()
    {
        int h = height(root);
        return h;
    }

    void remove(const T &d)
    {
        root = remove(root, d);
    }

    unsigned int size() { return size_; }
};

int main()
{
    Treap<int> Treap;
    Treap.insert(1);
    Treap.insert(2);
    Treap.insert(3);
    Treap.insert(4);
    Treap.insert(5);
    Treap.insert(6);
    // cout << "Tamaño: " << Treap.size() << endl;
    Treap.printInOrder();
    // Treap.printPreOrder();
    // Treap.IterativePreOrder();
    // Treap.printPostOrder();
    // Treap.printIterativePostOrder();
    cout << "Altura: " << Treap.height() << endl;
    Treap.remove(1);
    // cout << "Tamaño: " << Treap.size() << endl;
    Treap.printInOrder();
    cout << "Altura: " << Treap.height() << endl;
    return 0;
}