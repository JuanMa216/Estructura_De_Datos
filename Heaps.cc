#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

template <typename T>
class Heap
{
private:
    vector<T> arr;

    unsigned int leftChild(unsigned int pos) const
    {
        return (2 * pos) + 1;
    }

    unsigned int rightChild(unsigned int pos) const
    {
        return (2 * pos) + 2;
    }

    unsigned int parent(unsigned int pos) const
    {
        return (pos - 1) / 2;
    }

    void siftUp(unsigned int pos)
    {
        unsigned int parentPos = parent(pos);
        while (pos > 0 && arr[pos] < arr[parentPos])
        {
            swap(arr[pos], arr[parentPos]);
            pos = parentPos;
            parentPos = parent(pos);
        }
    }

    void siftDown(unsigned int pos)
    {
        while (true)
        {
            unsigned int leftC = leftChild(pos);
            unsigned int rightC = rightChild(pos);
            unsigned int smallest = pos;

            if (leftC < arr.size() && arr[leftC] < arr[smallest])
                smallest = leftC;
            if (rightC < arr.size() && arr[rightC] < arr[smallest])
                smallest = rightC;

            if (smallest != pos)
            {
                swap(arr[pos], arr[smallest]);
                pos = smallest;
            }
            else
            {
                break;
            }
        }
    }

public:
    Heap() : arr() {}

    void insert(const T &data)
    {
        arr.push_back(data);
        siftUp(arr.size() - 1);
    }

    T get_min() const
    {
        if (arr.size() == 0)
        {
            throw std::out_of_range("Heap is empty");
        }
        return arr[0];
    }

    T get_max() const
    {
        if (arr.size() == 0)
        {
            throw std::out_of_range("Heap is empty");
        }
        return arr[0];
    }

    T extract_min()
    {
        if (arr.size() == 0)
        {
            throw std::out_of_range("Heap is empty");
        }
        T min = arr[0];
        swap(arr[arr.size() - 1], arr[0]);
        arr.pop_back();
        siftDown(0);
        return min;
    }

    T extract_max()
    {
        if (arr.size() == 0)
        {
            throw std::out_of_range("Heap is empty");
        }
        T max = arr[0];
        swap(arr[arr.size() - 1], arr[0]);
        arr.pop_back();
        siftDown(0);
        return max;
    }

    void update(unsigned int pos, const T &new_data)
    {
        if (arr.size() == 0 || pos >= arr.size())
        {
            throw std::out_of_range("Heap is empty or index out of range");
        }

        T old = arr[pos];
        arr[pos] = new_data;

        if (new_data < old)
        {
            siftUp(pos); // Subir si es menor
        }
        else
        {
            siftDown(pos); // Bajar si es mayor
        }
    }

    void heapify()
    {
        for (int i = arr.size() / 2 - 1; i >= 0; i--)
            siftDown(i);
    }

    void loadFromVector(const vector<T> &v)
    {
        arr = v;
    }
};