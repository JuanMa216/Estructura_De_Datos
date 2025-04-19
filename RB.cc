#include <iostream>
using namespace std;

enum Color
{
    RED,
    BLACK
};

template <typename T>
class RB
{
private:
    class Node
    {
    private:
        T data_;
        Node *left_;
        Node *right_;
        Node *parent_;
        Color color_;

    public:
        Node(const T &data)
            : data_(data), left_(nullptr), right_(nullptr), parent_(nullptr), color_(RED) {}

        T getData() const { return data_; }
        void setData(const T &data) { data_ = data; }

        Node *getLeft() const { return left_; }
        void setLeft(Node *l) { left_ = l; }

        Node *getRight() const { return right_; }
        void setRight(Node *r) { right_ = r; }

        Color getColor() const { return color_; }
        void setColor(Color c) { color_ = c; }

        Node *getParent() const { return parent_; }
        void setParent(Node *p) { parent_ = p; }
    };

    Node *root;
    unsigned int size_;

    bool isRed(Node *node)
    {
        return node != nullptr && node->getColor() == RED;
    }

    Node *rotateLeft(Node *h)
    {
        Node *x = h->getRight();
        h->setRight(x->getLeft());
        x->setLeft(h);
        x->setColor(h->getColor());
        h->setColor(RED);
        return x;
    }

    Node *rotateRight(Node *h)
    {
        Node *x = h->getLeft();
        h->setLeft(x->getRight());
        x->setRight(h);
        x->setColor(h->getColor());
        h->setColor(RED);
        return x;
    }

    Node *insert(Node *h, const T &data)
    {
        if (h == nullptr)
        {
            size_++;
            Node *newNode = new Node(data);
            newNode->setColor(RED);
            return newNode;
        }

        if (data < h->getData())
        {
            h->setLeft(insert(h->getLeft(), data));
        }
        else if (data > h->getData())
        {
            h->setRight(insert(h->getRight(), data));
        }

        // Rebalancear
        if (isRed(h->getRight()) && !isRed(h->getLeft()))
        { // (rotación izquierda)
            h = rotateLeft(h);
        }
        if (isRed(h->getLeft()) && isRed(h->getLeft()->getLeft()))
        { // (rotacion derecha)
            h = rotateRight(h);
        }
        if (isRed(h->getLeft()) && isRed(h->getRight()))
        { // (cambio de color)
            h->setColor(RED);
            h->getLeft()->setColor(BLACK);
            h->getRight()->setColor(BLACK);
        }

        return h;
    }

    void printInOrder(Node *node)
    {
        if (node == nullptr)
            return;
        printInOrder(node->getLeft());
        cout << node->getData() << " -> ";
        printInOrder(node->getRight());
    }

    bool empty() const { return root == nullptr; }

    int height(Node *node)
    {
        if (!node)
            return -1; // convention: height of empty tree is -1
        int leftHeight = height(node->getLeft());
        int rightHeight = height(node->getRight());
        return 1 + max(leftHeight, rightHeight);
    }

    Node *search(const T &data, Node *node)
    {
        if (empty())
        {
            return node;
        }

        if (node != nullptr || node->getData() == data)
        {
            return node;
        }

        if (data < node->getData())
        {
            return search(data, node->getLeft());
        }
        else
        {
            return search(data, node->getRight());
        }
    }

public:
    RB() : root(nullptr), size_(0) {}
    /*
        void fixInsert(Node *n)
        {
            Node *uncle;
            while (n != root && n->getParent()->getColor() == RED)
            {
                if (n->getParent() == n->getParent()->getParent()->getLeft())
                {
                    uncle = n->getParent()->getParent()->getRight(); // tío
                    if (uncle != nullptr && uncle->getColor() == RED)
                    {
                        // Caso 1: El tío es rojo => recolorear
                        n->getParent()->setColor(BLACK);
                        uncle->setColor(BLACK);
                        n->getParent()->getParent()->setColor(RED);
                        n = n->getParent()->getParent();
                    }
                    else
                    {
                        if (n == n->getParent()->getRight())
                        {
                            // Caso 2: El nodo es hijo derecho => rotar
                            n = n->getParent();
                            rotateLeft(n);
                        }
                        // Caso 3: El nodo es hijo izquierdo
                        n->getParent()->setColor(BLACK);
                        n->getParent()->getParent()->setColor(RED);
                        rotateRight(n->getParent()->getParent());
                    }
                }
                else
                {
                    // Simétrico: el padre es hijo derecho
                    uncle = n->getParent()->getParent()->getLeft();
                    if (uncle != nullptr && uncle->getColor() == RED)
                    {
                        // Caso 1
                        n->getParent()->setColor(BLACK);
                        uncle->setColor(BLACK);
                        n->getParent()->getParent()->setColor(RED);
                        n = n->getParent()->getParent();
                    }
                    else
                    {
                        if (n == n->getParent()->getLeft())
                        {
                            // Caso 2
                            n = n->getParent();
                            rotateRight(n);
                        }
                        // Caso 3
                        n->getParent()->setColor(BLACK);
                        n->getParent()->getParent()->setColor(RED);
                        rotateLeft(n->getParent()->getParent());
                    }
                }
            }
            root->setColor(BLACK);
        }

        void insert(const T &data)
        {
            Node *n = new Node(data);
            if (empty())
            {
                root = n;
                root->setColor(BLACK);
                size_ += 1;
                return;
            }
            Node *current = root;
            Node *parent = nullptr;
            while (current != nullptr)
            {
                parent = current;
                if (data < current->getData())
                {
                    current = current->getLeft();
                }
                else
                {
                    current = current->getRight();
                }
            }

            if (data < parent->getData())
            {
                parent->setLeft(n);
            }
            else
            {
                parent->setRight(n);
            }

            n->setParent(parent);
            size_++;
            fixInsert(n);
        }
    */
    void insert(const T &data)
    {
        root = insert(root, data);
        root->setColor(BLACK);
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

    bool search(const T &data)
    {
        return search(data, root) != nullptr;
    }
};

int main()
{
    RB<int> MyRBTree;
    MyRBTree.insert(3);
    MyRBTree.insert(4);
    MyRBTree.insert(5);
    MyRBTree.insert(1);
    MyRBTree.insert(2);
    MyRBTree.print();
    cout << "Altura: " << MyRBTree.height() << endl;
    if (MyRBTree.search(1))
    {
        cout << "El valor de 1 ha sido encontrado." << endl;
    }
    else
    {
        cout << "El valor de 1 no ha sido encontrado." << endl;
    }

    return 0;
}
