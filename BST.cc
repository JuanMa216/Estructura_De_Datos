#include <iostream>

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
};

int main()
{
    cout << "Binary Search Trees!" << endl;
    BST<int> MyTree;

    MyTree.insert(3);
    MyTree.insert(2);
    MyTree.insert(4);
    MyTree.insert(5);
    MyTree.insert(1);
    MyTree.print();
    cout << "Size: " << MyTree.size() << endl;
    MyTree.findEQ(3);
    MyTree.findEQ(6);
    MyTree.findEQ(1);
    MyTree.add(6);
    MyTree.print();
    cout << "Size: " << MyTree.size() << endl;
    MyTree.findEQ(6);
    return 0;
}
