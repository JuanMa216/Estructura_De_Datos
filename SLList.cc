#include <iostream>

using namespace std;

template <typename T>

class SLL {
private:
    class Node {
        private: 
        T data_;
        Node* next_;

        public:
        Node() {
            data_ = T();
            next_ = nullptr;
        }

        Node(const T& d) {
            data_ = d;
            next_ = nullptr;
        }

        T getData() const {
            return data_;
        }

        Node* getNext() const {
            return next_;
        }

        void setNext(Node* nxt) {
            next_ = nxt;
        }

        void setData(const T& data) {
            data_ = data;
        }
    };

private:
    Node *first_;
    Node *last_;
    unsigned int size_;
public:
    SLL() {
        first_ = nullptr;
        last_ = nullptr;
        size_ = 0;
    }

    bool empty() const { return first_ == nullptr; }

    unsigned int size() const { return size_; }

    void push_front(const T& d) {
        Node *n = new Node(d); //Crea un nuevo nodo con el valor d.

        n->setNext(first_); //Hace que el nuevo nodo n apunte al nodo que se encuentra en first_.
        first_ = n; //Hace que first_ apunte al nuevo nodo n.

        if(size_ == 0) { //Caso especial en el que la lista esta vacia, n es tanto first_ como last_.
            last_ = n;
        }

        size_++; //Se aumenta el tamaño de la lista.
    }

    void push_back(const T& d) {
        Node *n = new Node(d); // Crea un nuevo nodo con el valor d.
    
        if(empty()) { // Si la lista está vacía (first_ es nullptr o size_ es 0), el nuevo nodo será el único elemento.
            first_ = n; 
            last_ = n;  // Tanto first_ como last_ apuntan al nuevo nodo, ya que es el único en la lista.
        } else { 
            last_->setNext(n); // Enlaza el último nodo actual con el nuevo nodo.
            last_ = n;         // Actualiza last_ para que apunte al nuevo último nodo.
        }
    
        size_++; // Incrementa el tamaño de la lista.
    }
    
    void insert(const T& d, unsigned int pos) {
        Node *n = new Node(d); // Se crea un nuevo nodo con el valor `d`.
    
        if (pos > size_) return; // Si la posición es inválida (mayor que `size_`), no se inserta nada.
    
        // Caso especial: insertar al inicio (equivalente a `push_front`).
        if (pos == 0) { 
            n->setNext(first_); // Enlaza el nuevo nodo con el actual primer nodo.
            first_ = n; // `first_` ahora apunta al nuevo nodo `n`.
            size_++; // Se incrementa el tamaño de la lista.
            //push_front(d);
            return;
        }
    
        // Recorremos la lista hasta el nodo anterior a `pos`.
        Node *current = first_;
        for (unsigned int i = 0; i < pos - 1; i++) {
            current = current->getNext(); // Avanza `current` a la posición deseada.
        }
    
        // Inserción del nuevo nodo en `pos`.
        n->setNext(current->getNext()); // `n` apunta al siguiente nodo después de `current`.
        current->setNext(n); // `current` ahora apunta al nuevo nodo `n`.
    
        // Caso especial: si `n` es el último nodo, actualizamos `last_`.
        if (n->getNext() == nullptr) {
            last_ = n;
        }
        
        size_++; // Incrementamos el tamaño de la lista.
    }
    

    bool search(const T& d) {
        Node *current = first_;
        while (current != nullptr)
        {
            if(current->getData() == d) {
                return true;
            }
        current = current->getNext();
        }
    return false;
    }

    void pop_front() {
        if(empty()) return; // Si la lista está vacía, no hay nada que eliminar.
    
        Node *temp = first_; // Guarda el nodo que será eliminado (el actual `first_`).
        first_ = first_->getNext(); // `first_` avanza al siguiente nodo (si existe).
    
        delete temp; // Libera la memoria del nodo eliminado.
    
        // Caso especial: si la lista quedó vacía después de eliminar el nodo, actualizamos `last_`.
        if (first_ == nullptr) {
            last_ = nullptr;
        }
    
        size_--; // Se reduce el tamaño de la lista tras eliminar el nodo.
    }

    void pop_back() {
        if (empty()) return; // Si la lista está vacía, no hay nada que eliminar.
    
        if (first_->getNext() == nullptr) { // Si solo hay un elemento en la lista.
            pop_front();
            return;
        }
    
        Node *current = first_;
        while (current->getNext()->getNext() != nullptr) { // Recorremos hasta el penúltimo nodo.
            current = current->getNext();
        }
    
        delete current->getNext(); // Eliminamos el último nodo.
        current->setNext(nullptr); // El penúltimo nodo ahora es el último.
    
        last_ = current; // Actualizamos `last_` al nuevo último nodo.
        size_--; // Reducimos el tamaño de la lista.
    }

    void remove(unsigned int pos) {
        if(pos >= size_ || first_ == nullptr) return;

        if(pos == 0) {
            pop_front();
            return;
        }

        Node *current = first_;
        Node *toDelete;
        for (unsigned int i = 0; i < pos - 1; i++)
        {
            current = current->getNext();
        }
        toDelete = current->getNext();
        current->setNext(toDelete->getNext());

        if (toDelete->getNext() == nullptr)
        {
            last_ = current;
        }
        
        delete toDelete;
        size_--;
    }
    
    void modify(unsigned int pos, T d) {
        if(pos >= size_ || first_ == nullptr) return;
        Node *current = first_;
        
        for (unsigned int i = 0; i < pos; i++)
        {
            current = current->getNext();
        }

        current->setData(d);
    }
    

    void print() {
        if(size_ == 0) return;
        Node *current = first_;
        while (current != nullptr)
        {
            cout << current->getData() << " -> ";
            current = current->getNext();   
        }
    cout << "nullptr" << endl;
    }

};

int main() {
    cout << "Listas!" << endl;
    SLL<int> MyList;

    MyList.push_front(3);
    MyList.push_front(2);
    MyList.push_front(1);

    MyList.print();
    cout << "Size: " << MyList.size() << endl;

    MyList.push_back(4);
    MyList.push_back(5);

    MyList.print();
    
    cout << "Size: " << MyList.size() << endl;

    int x = 5;
    if(MyList.search(x)) {
        cout << "Se encontró el dato: "<< x << endl;
    } else {
        cout << "No se ha encontrado el dato: " << x << endl;
    }

    MyList.insert(100, 1);
    MyList.print();

    MyList.pop_front();
    MyList.print();

    cout << "Size: " << MyList.size() << endl;
    MyList.pop_back();
    MyList.print();

    MyList.push_back(9);
    MyList.push_back(2);
    MyList.print();
    MyList.remove(2);
    MyList.print();

    MyList.modify(2, 69);
    MyList.print();
    return 0;
}