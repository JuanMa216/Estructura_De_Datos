#include <iostream>
#include <cassert>

using namespace std;

template <typename T>
class Vector {
    private:
    T* storage_;
    unsigned int capacity_;
    unsigned int size_;
    public:
    Vector(unsigned int c) {
        capacity_ = c;
        storage_ = new T[capacity_];
        size_ = 0;
    }

    Vector() {
        capacity_ = 5;
        storage_ = new T[capacity_];
        size_ = 0;
    }

    Vector(unsigned int c, T elem) {
        capacity_ = c;
        storage_ = new T[capacity_];
        for (unsigned int i = 0; i < capacity_; i++) {
            storage_[i] = elem;
        }
    size_ = capacity_;
    }

    public:
    unsigned int capacity() {
        return capacity_;
    }

    unsigned int size() {
        return size_;
    }

    T& at(unsigned int pos) {
        assert(pos >= 0 && pos < size_);
        return storage_[pos];
    }

    const T& at(unsigned int pos) const {
        assert(pos >= 0 && pos < size_);
        return storage_[pos];
    }

    const T& operator[](unsigned int index) const {
        return storage_[index];
    }

    private:
    void resize() {
        cout << "Resize" << endl;
        unsigned int capacity2 = capacity_ * 1.5;
        T* storage2 = new T[capacity2];
        for ( unsigned int i = 0; i < size_; i++) {
            storage2[i] = storage_[i];
        }
        delete [] storage_;
        storage_ = storage2;
        capacity_ = capacity2;
    }

    public:
    unsigned int waste() {
        return capacity_ - size_;
    }

    void push_front(const T& elem) {
        if (size_ == capacity_)
        {
            resize();
        }

        for (unsigned int i = size_; i > 0; i--) {
            swap(storage_[i], storage_[i - 1]);
        }
        storage_[0] = elem;
        size_++;
    }

    void push_back(const T& elem) {
        if (size_ == capacity_) {
            resize();
        }
        storage_[size_] = elem;
        size_++;
    }

    void pop_back() {
        if(size_ == 0) return;
        size_--;
    }

    void pop_front() {
        if(size_ == 0) return;
        for (unsigned int i = 0; i < size_ - 1; i++) {
            storage_[i] = storage_[i + 1];
        }
        size_--;
    }

    void insert(unsigned int index, T element) {
        if (index > size_)
        {
            throw std::out_of_range("Index out of bounds");
        }

        if (size_ == capacity_)
        {
            resize();
        }

        for (unsigned int i = size_; i > size_; i--)
        {
            storage_[i] = storage_[i-1];
        }
        
        storage_[index] = element;
        size_++;
    }

    void print() {
        for (unsigned int i = 0; i < size_; i++) {
            cout << " " << storage_[i];
        }
        cout << endl;
    }

};

int main() {
    
    Vector<int> myVector(3);
    myVector.push_back(10);
    myVector.push_back(20);
    myVector.push_back(30);

    cout << myVector.size() << endl; // Expected: 3
    cout << myVector.capacity() << endl; // Expected: Initial capacity, e.g., 4 or 8

    // Test pop_back
    myVector.pop_back();
    cout << myVector.size() << endl; // Expected: 2

    // Test at with valid and invalid indices
    cout << myVector.at(0) << endl; // Expected: 10
    cout << myVector.at(1) << endl; // Expected: 20

    myVector.print();
    myVector.insert(0,1);
    myVector.print();
    myVector.insert(1,2);
    myVector.print();
    myVector.insert(2,3);
    myVector.print();
    myVector.insert(6,4);
    myVector.print();
    //myVector.insert(3,4);
    //myVector.print();

    // Border case: Accessing an out-of-bounds index
    //cout << myVector.at(2) << endl; // Should crash!

    // Border case: pop_back on empty vector
    //Vector<int> emptyVector;
    //emptyVector.pop_back(); // should crash!

    return 0;
}