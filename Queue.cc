#include <iostream>
#include <cassert>
using namespace std;

template <typename T>
class Vector
{
private:
    T *storage_;
    unsigned int capacity_;
    unsigned int size_;

public:
    Vector(unsigned int c)
    {
        capacity_ = c;
        storage_ = new T[capacity_];
        size_ = 0;
    }

    Vector()
    {
        capacity_ = 5;
        storage_ = new T[capacity_];
        size_ = 0;
    }

    Vector(std::initializer_list<T> list)
    {
        capacity_ = list.size();
        size_ = list.size();
        storage_ = new T[capacity_];

        unsigned int i = 0;
        for (const T &elem : list)
        {
            storage_[i++] = elem;
        }
    }

    void resize()
    {
        cout << "Resize" << endl;
        unsigned int capacity2 = capacity_ * 1.5;
        T *storage2 = new T[capacity2];
        for (unsigned int i = 0; i < size_; i++)
        {
            storage2[i] = storage_[i];
        }
        delete[] storage_;
        storage_ = storage2;
        capacity_ = capacity2;
    }

public:
    unsigned int capacity() const
    {
        return capacity_;
    }

    unsigned int size() const
    {
        return size_;
    }

    void push_back(const T &elem)
    {
        if (size_ == capacity_)
        {
            resize();
        }
        storage_[size_] = elem;
        size_++;
    }

    void pop_back()
    {
        if (size_ == 0)
            throw std::underflow_error("Cannot pop from an empty array");
        size_--;
    }

    bool empty() const { return size_ == 0; }

    T &at(unsigned int pos)
    {
        assert(pos < size_ && pos >= 0);
        return storage_[pos];
    }

    const T &at(unsigned int pos) const
    {
        assert(pos < size_ && pos >= 0);
        return storage_[pos];
    }
};

template <typename T>
class Queue
{
private:
    Vector<T> storage_;

public:
    Queue()
    {
        storage_ = Vector<T>();
    }
    // Empty operation: Verifica si la cola está vacía.
    bool empty() const
    {
        return storage_.empty();
    }

    // Enqueue operation: Insertamos un elemento al final de la cola.
    void enqueue(const T &elem)
    {
        storage_.push_back(elem);
    }

    // Dequeue operation: Eliminamos el primer elemento de la cola.

    void dequeue()
    {
        if (empty())
        {
            throw std::underflow_error("Cannot dequeue from an empty queue");
        }

        for (unsigned int i = 0; i < storage_.size() - 1; i++)
        {
            storage_.at(i) = storage_.at(i + 1);
        }
        storage_.pop_back();
    }

    // Front operation: Obtenemos el primer elemento de la cola.
    T front() const
    {
        if (empty())
        {
            throw std::underflow_error("Cannot get front from an empty queue");
        }
        return storage_.at(0);
    }

    // Size operation: Obtenemos el tamaño de la cola.
    unsigned int size() const
    {
        return storage_.size();
    }

    // Display operation: Imprimimos los elementos de la cola.
    void display() const
    {
        for (unsigned int i = 0; i < storage_.size(); i++)
        {
            cout << storage_.at(i) << " ";
        }
        cout << endl;
    }

    // Clear operation: Eliminamos todos los elementos de la cola.
    void clear()
    {
        while (!empty())
        {
            dequeue();
        }
    }
};

int main()
{
    Queue<int> myQueue;
    myQueue.enqueue(1);
    myQueue.enqueue(2);
    myQueue.enqueue(3);
    myQueue.enqueue(4);
    myQueue.display();
    myQueue.dequeue();
    myQueue.display();
    cout << "Front: " << myQueue.front() << endl;
    cout << "Size: " << myQueue.size() << endl;
    myQueue.clear();
    myQueue.display();

    return 0;
}