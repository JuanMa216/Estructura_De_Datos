#include <iostream>
#include <random>
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
            size_++;
            return new Node(data, distrib(gen));
        }
        //Buscamos donde quedará el nuevo nodo.
        if (data < root->getData())
            root->setLeft(insert(root->getLeft(), data));
        else
            root->setRight(insert(root->getRight(), data));
        //Balanceamos.
        if (root->getLeft() != nullptr && root->getLeft()->getPriority() > root->getPriority())

            root = rotateRight(root);
        else if (root->getRight() != nullptr && root->getRight()->getPriority() > root->getPriority())
            root = rotateLeft(root);

        return root;
    }

    void printInOrder(Node *node)
    {
        if (node == nullptr)
            return;
        printInOrder(node->getLeft());
        cout << "(" << node->getData() << ", " << node->getPriority() << ")" << " -> ";
        printInOrder(node->getRight());
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

    void print()
    {
        if (empty())
            return;
        printInOrder(root);
        cout << "nullptr" << endl;
    }

    int height()
    {
        int h = height(root);
        return h;
    }
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
    Treap.print();
    cout << "Altura: " << Treap.height() << endl;
    return 0;
}