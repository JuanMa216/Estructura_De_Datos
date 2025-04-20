#include <iostream>
using namespace std;

enum Color
{
    RED,  // Red = 0
    BLACK // Black = 1
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
        if (node == nullptr)
            return nullptr;

        if (data == node->getData())
            return node;

        if (data < node->getData())
            return search(data, node->getLeft());
        else
            return search(data, node->getRight());
    }

    Node *findMin(Node *n)
    {
        while (n != nullptr && n->getLeft() != nullptr)
            n = n->getLeft();
        return n;
    }

    void fixDelete(Node *node)
    {
        while (node != root && !isRed(node))
        {
            if (node == node->getParent()->getLeft()) // Caso 1: Nodo es hijo izquierdo
            {
                Node *sibling = node->getParent()->getRight();

                if (isRed(sibling)) // Caso 1.1: Hermano rojo
                {
                    sibling->setColor(BLACK);
                    node->getParent()->setColor(RED);
                    rotateLeft(node->getParent());
                    sibling = node->getParent()->getRight();
                }

                if (!isRed(sibling->getLeft()) && !isRed(sibling->getRight())) // Caso 1.2: Hermano negro con hijos negros
                {
                    sibling->setColor(RED);
                    node = node->getParent();
                }
                else
                {
                    if (!isRed(sibling->getRight())) // Caso 1.3: Hermano negro con hijo izquierdo rojo
                    {
                        sibling->getLeft()->setColor(BLACK);
                        sibling->setColor(RED);
                        rotateRight(sibling);
                        sibling = node->getParent()->getRight();
                    }

                    sibling->setColor(node->getParent()->getColor());
                    node->getParent()->setColor(BLACK);
                    sibling->getRight()->setColor(BLACK);
                    rotateLeft(node->getParent());
                    node = root;
                }
            }
            else // Caso 2: Nodo es hijo derecho (simétrico al caso 1)
            {
                Node *sibling = node->getParent()->getLeft();

                if (isRed(sibling)) // Caso 2.1: Hermano rojo
                {
                    sibling->setColor(BLACK);
                    node->getParent()->setColor(RED);
                    rotateRight(node->getParent());
                    sibling = node->getParent()->getLeft();
                }

                if (!isRed(sibling->getLeft()) && !isRed(sibling->getRight())) // Caso 2.2: Hermano negro con hijos negros
                {
                    sibling->setColor(RED);
                    node = node->getParent();
                }
                else
                {
                    if (!isRed(sibling->getLeft())) // Caso 2.3: Hermano negro con hijo derecho rojo
                    {
                        sibling->getRight()->setColor(BLACK);
                        sibling->setColor(RED);
                        rotateLeft(sibling);
                        sibling = node->getParent()->getLeft();
                    }

                    sibling->setColor(node->getParent()->getColor());
                    node->getParent()->setColor(BLACK);
                    sibling->getLeft()->setColor(BLACK);
                    rotateRight(node->getParent());
                    node = root;
                }
            }
        }

        node->setColor(BLACK); // El nodo actual debe ser negro para restaurar las propiedades
    }

    Node *remove(Node *node, const T &d)
    {
        if (node == nullptr)
            return nullptr;

        if (d < node->getData())
        {
            node->setLeft(remove(node->getLeft(), d));
        }
        else if (d > node->getData())
        {
            node->setRight(remove(node->getRight(), d));
        }
        else
        {
            // Caso 1: Hoja.
            if (node->getLeft() == nullptr && node->getRight() == nullptr)
            {
                delete node;
                size_--;
                return nullptr;
            }
            else if (node->getLeft() == nullptr || node->getRight() == nullptr)
            { // Caso 2: Un hijo.
                Node *temp = nullptr;
                if (node->getLeft() != nullptr)
                {
                    temp = node->getLeft();
                }
                else
                {
                    temp = node->getRight();
                }
                temp->setParent(node->getParent());
                delete node;
                size_--;
                return temp;
            }
            else if (node->getLeft() != nullptr && node->getRight() != nullptr)
            { // Caso 3: Dos hijos.
                Node *minNode = findMin(node->getRight());
                node->setData(minNode->getData());                            // Copiar Dato.
                node->setRight(remove(node->getRight(), minNode->getData())); // Eliminar el sucesor.
            }
        }
        fixDelete(node);
        return node;
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

    unsigned int size() const { return size_; }

    void remove(const T &d)
    {
        root = remove(root, d);
    }
};

int main()
{
    RB<int> tree;
    tree.insert(12);
    tree.insert(15);
    tree.insert(3);
    tree.insert(4);
    tree.insert(2);
    tree.print();
    cout << "Altura: " << tree.height() << endl;
    if (tree.search(1))
    {
        cout << "El valor de 1 ha sido encontrado." << endl;
    }
    else
    {
        cout << "El valor de 1 no ha sido encontrado." << endl;
    }

    cout << "Tamaño: " << tree.size() << endl;
    tree.remove(15);
    tree.print();
    cout << "Altura: " << tree.height() << endl;
    cout << "Tamaño: " << tree.size() << endl;
    return 0;
}
