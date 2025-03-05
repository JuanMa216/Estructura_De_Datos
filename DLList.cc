#include <iostream>

using namespace std;

template <typename T>

class DLL {
private:
    class Node {
        private:
        T data_;
        Node* next_;
        Node* prev_;

        public:
        Node() {
            data_ = T();
            prev_ = next_ = nullptr;
        }

        Node(const T& d) {
            data_ = d;
            prev_ = next_ = nullptr;
        }
    }; 

};
    