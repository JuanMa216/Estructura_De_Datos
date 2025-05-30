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

    void pop_front() {
        if(size_ == 0) return;
        for (unsigned int i = 0; i < size_ - 1; i++) {
            storage_[i] = storage_[i + 1];
        }
        size_--;
    }

    

    void print() {
        for (unsigned int i = 0; i < size_; i++) {
            cout << " " << storage_[i];
        }
        cout << endl;
    }

    void insert(unsigned int index,T element) {
        assert(index < size_);

        if(index == 0) {
            push_front(element);
            return;
        }

        if (index == size_ - 1)
        {
            push_back(element);
            return;
        }
        
        if (size_ == capacity_)
        {
            resize();
        }

        for (unsigned int i = size_; i > index; i--)
        {
            storage_[i] = storage_[i-1];
        }
        
        storage_[index] = element;
        size_++;
    }

    void pop_back() {
        if(size_ == 0) return;
        size_--;
    }
    
    void erase(unsigned int index) {
        assert(index >= 0 && index < size_);
    
        if(index == 0) {
            pop_front();
            return;
        }
    
        if (index == size_ - 1)
        {
            pop_back();
            return;
        }
    
        for (unsigned int i = index; i < size_ ; i++)
        {
            storage_[i] = storage_[i + 1];
        }
        
    size_--;
    }
};

int main() {
    Vector<int> MyVector(3);
    MyVector.push_front(1);
    MyVector.push_front(2);
    MyVector.push_front(3);
    cout << "Tamaño: " << MyVector.size() << endl;
    MyVector.print();
    MyVector.insert(1,4);
    MyVector.insert(2,5);
    MyVector.print();
    MyVector.erase(0);
    MyVector.erase(2);
    MyVector.erase(MyVector.size()-1);
    MyVector.print();
    
    return 0;
}