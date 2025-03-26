#include <iostream>

using namespace std;

template <typename T>

class DLL
{
private:
    class Node
    {
    private:
        T data_;
        Node *next_;
        Node *prev_;

    public:
        Node()
        {
            data_ = T();
            prev_ = next_ = nullptr;
        }

        Node(const T &d)
        {
            data_ = d;
            prev_ = next_ = nullptr;
        }

        T getData() const
        {
            return data_;
        }

        Node *getNext() const
        {
            return next_;
        }

        Node *getPrev() const
        {
            return prev_;
        }

        void setNext(Node *nxt)
        {
            next_ = nxt;
        }

        void setPrev(Node *prv)
        {
            prev_ = prv;
        }

        void setData(const T &data)
        {
            data_ = data;
        }
    };

private:
    Node *first_;
    Node *last_;
    unsigned int size_;

public:
    DLL()
    {
        first_ = last_ = nullptr;
        size_ = 0;
    }

    bool empty() const { return first_ == nullptr; }

    unsigned int size() const { return size_; }

    void print()
    {
        Node *current = first_;
        while (current != nullptr)
        {
            cout << current->getData() << " -> ";
            current = current->getNext();
        }
        cout << "nullptr" << endl;
    }

    void push_front(const T &d)
    {
        Node *n = new Node(d);

        n->setNext(first_);

        if (first_ != nullptr)
        {
            first_->setPrev(n);
        }

        first_ = n;

        if (size_ == 0)
        {
            last_ = n;
        }

        size_++;
    }
};

int main()
{
    cout << "Listas Dobles!" << endl;

    DLL<int> myList;
    myList.push_front(1);
    myList.print();
    myList.push_front(2);
    myList.push_front(3);
    myList.print();

    return 0;
}
