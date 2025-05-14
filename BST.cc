#include <iostream>
#include <queue>
#include <Queue>

using namespace std;
template <typename T>

class BST
{
private:
    class Node
    {
    private:
        T data_;
        Node *left_;
        Node *right_;

    public:
        Node()
        {
            data_ = T();
            left_ = nullptr;
            right_ = nullptr;
        }

        Node(const T &d)
        {
            data_ = d;
            left_ = nullptr;
            right_ = nullptr;
        }

        T getData() const
        {
            return data_;
        }

        Node *getLeft() const
        {
            return left_;
        }

        Node *getRight() const
        {
            return right_;
        }

        void setLeft(Node *l)
        {
            left_ = l;
        }

        void setRight(Node *r)
        {
            right_ = r;
        }

        void setData(const T &data)
        {
            data_ = data;
        }
    };

private:
    Node *root;
    unsigned int size_;

    void levelOrder(Node *node)
    {
        if (node == nullptr)
            return;
        queue<Node *> Q;
        Q.push(node);
        while (!Q.empty())
        {
            Node *current = Q.front();
            Q.pop();

            cout << " " << current->getData();

            if (current->getLeft() != nullptr)
                Q.push(current->getLeft());

            if (current->getRight() != nullptr)
                Q.push(current->getRight());
        }
    }

public:
    BST()
    {
        root = nullptr;
        size_ = 0;
    }

    bool empty() const { return root == nullptr; }

    unsigned int size() const { return size_; }

    void insert(const T &d)
    {
        Node *n = new Node(d);
        if (empty())
        {
            root = n;
            size_++;
            return;
        }
        else
        {
            Node *current = root;
            Node *parent = nullptr;
            while (current != nullptr)
            {
                parent = current;
                if (d < current->getData())
                {
                    current = current->getLeft();
                }
                else
                {
                    current = current->getRight();
                }
            }
            if (d < parent->getData())
            {
                parent->setLeft(n);
            }
            else
            {
                parent->setRight(n);
            }
            size_++;
        }
    }

    void print()
    {
        if (empty())
            return;
        printInOrder(root);
        cout << "nullptr" << endl;
    }

    void printInOrder(Node *node)
    {
        if (node == nullptr)
            return;
        printInOrder(node->getLeft());
        cout << node->getData() << " -> ";
        printInOrder(node->getRight());
    }

    T findEQ(const T &d)
    {
        if (empty())
            return T();
        Node *current = root;
        while (current != nullptr)
        {
            if (d == current->getData())
            {
                cout << "Found!" << endl;
                return current->getData();
            }
            else if (d < current->getData())
            {
                current = current->getLeft();
            }
            else
            {
                current = current->getRight();
            }
        }
        cout << "Not found!" << endl;
        return T();
    }

    bool add(const T &d)
    {
        Node *n = new Node(d);
        if (empty())
        {
            root = n;
            size_++;
            return true;
        }

        Node *p = findLast(d);
        return addChild(p, n);
        return true;
    }

    Node *findLast(const T &d)
    {
        Node *current = root;
        Node *parent = nullptr;
        while (current != nullptr)
        {
            parent = current;
            if (d < current->getData())
            {
                current = current->getLeft();
            }
            else
            {
                current = current->getRight();
            }
        }
        return parent;
    }

    bool addChild(Node *p, Node *u)
    {
        if (p == nullptr)
        {
            root = u;
        }
        else
        {
            if (u->getData() < p->getData())
            {
                p->setLeft(u);
            }
            else
            {
                p->setRight(u);
            }
        }
        size_++;
        return true;
    }

    void remove(const T &d)
    {
        if (empty())
        {
            cout << "Tree is empty!" << endl;
            return;
        }

        Node *p = nullptr;
        Node *current = root;

        // Buscar el nodo a eliminar
        while (current != nullptr && current->getData() != d)
        {
            p = current;
            if (d < current->getData())
            {
                current = current->getLeft();
            }
            else
            {
                current = current->getRight();
            }
        }

        // Si el nodo no se encuentra
        if (current == nullptr)
        {
            cout << "Node not found!" << endl;
            return;
        }

        // Caso 1: Nodo sin hijos (nodo hoja)
        if (current->getLeft() == nullptr && current->getRight() == nullptr)
        {
            if (p == nullptr)
            {
                root = nullptr; // El nodo a eliminar es la raíz
            }
            else
            {
                if (p->getLeft() == current)
                {
                    p->setLeft(nullptr);
                }
                else
                {
                    p->setRight(nullptr);
                }
            }
            delete current; // Liberar memoria
        }
        // Caso 2: Nodo con un solo hijo
        else if (current->getLeft() == nullptr || current->getRight() == nullptr)
        {
            Node *child;
            if (current->getLeft() != nullptr)
            {
                child = current->getLeft();
            }
            else
            {
                child = current->getRight();
            }

            if (p == nullptr)
            {
                root = child; // Si el nodo a eliminar es la raíz
            }
            else
            {
                if (p->getLeft() == current)
                {
                    p->setLeft(child);
                }
                else
                {
                    p->setRight(child);
                }
            }

            delete current; // Liberar memoria
        }
        // Caso 3: Nodo con dos hijos
        else
        {
            Node *succ = current->getRight();
            Node *psucc = current;

            // Buscar el nodo más pequeño en el subárbol derecho
            while (succ->getLeft() != nullptr)
            {
                psucc = succ;
                succ = succ->getLeft();
            }

            // Conectar el hijo derecho del sucesor con su padre
            if (psucc->getLeft() == succ)
            {
                psucc->setLeft(succ->getRight());
            }
            else
            {
                psucc->setRight(succ->getRight());
            }

            // Reemplazar `current` con `succ`
            succ->setLeft(current->getLeft());
            succ->setRight(current->getRight());

            if (p == nullptr)
            {
                root = succ;
            }
            else
            {
                if (p->getLeft() == current)
                {
                    p->setLeft(succ);
                }
                else
                {
                    p->setRight(succ);
                }
            }

            delete current; // Eliminar el nodo original
        }

        size_--;
    }

    void LevelOrderPrint()
    {
        levelOrder(root);
    }
};

int main()
{
    cout << "Binary Search Trees!" << endl;
    BST<int> MyTree;

    MyTree.insert(5);
    MyTree.insert(3);
    MyTree.insert(2);
    MyTree.insert(1);
    MyTree.insert(4);
    MyTree.insert(8);
    MyTree.insert(6);
    MyTree.insert(7);
    MyTree.insert(9);
    MyTree.insert(10);
    MyTree.print();
    MyTree.remove(5);
    MyTree.print();
    MyTree.remove(6);
    MyTree.print();
    MyTree.LevelOrderPrint();
    return 0;
}