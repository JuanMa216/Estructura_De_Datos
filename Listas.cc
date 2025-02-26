#include <iostream>

using namespace std;

template <typename T>
class List {
private:
    // Clase interna que representa un nodo de la lista
    class Node {
    private:
        T data_;       // Dato almacenado en el nodo
        Node* next_;   // Puntero al siguiente nodo

    public:
        // Constructor por defecto: inicializa data_ con el valor por defecto de T
        // y next_ con nullptr, indicando que el nodo no apunta a otro nodo.
        Node() {
            data_ = T(); 
            next_ = nullptr;
        }

        // Constructor que recibe un valor para el nodo
        Node(const T& d) {
            data_ = d;
            next_ = nullptr;
        }

        // Setter para asignar el siguiente nodo
        void setNext(Node* nxt) {
            next_ = nxt;
        }

        // Getter para obtener el siguiente nodo
        Node* getNext() const {
            return next_;
        }

        // Getter para obtener el dato almacenado en el nodo
        T getData() const {
            return data_;
        }

        
    };

private:
    Node* first_;    // Puntero al primer nodo de la lista
    Node* last_;     // Puntero al último nodo de la lista
    unsigned int size_; // Número de elementos en la lista

public:
    // Constructor: Inicializa una lista vacía
    List() {
        first_ = nullptr; // No hay primer nodo aún
        last_ = nullptr;  // No hay último nodo aún
        size_ = 0;        // La lista está vacía
    }

    // Devuelve el tamaño de la lista
    unsigned int size() const { return size_; }

    // Retorna true si la lista está vacía, false si tiene elementos
    bool empty() const { return first_ == nullptr; }

    // Inserta un elemento al inicio de la lista
    void push_front(const T& elem) {
        Node* n = new Node(elem);  // Crea un nuevo nodo con el valor elem
        n->setNext(first_);        // Apunta al nodo que era el primero antes
        first_ = n;                // El nuevo nodo ahora es el primero

        // Si la lista estaba vacía, también actualizamos last_
        if (size_ == 0) {
            last_ = n;
        }

        size_++; // Incrementamos el tamaño de la lista
    }

    // Inserta un elemento al final de la lista
    void push_back(const T& elem) {
        Node* n = new Node(elem); // Crea un nuevo nodo con el valor elem
        
        if (empty()) { // Si la lista está vacía
            first_ = n; // El primer nodo también será el último
            last_ = n;
        } else {
            last_->setNext(n); // El último nodo actual apunta al nuevo nodo
            last_ = n;         // Actualizamos last_ para que apunte al nuevo nodo
        }

        size_++; // Incrementamos el tamaño de la lista
    }

    // Método para imprimir la lista 
    void print() const {
        Node* current = first_; // Empezamos desde el primer nodo
        while (current != nullptr) { // Recorremos la lista hasta el final
            cout << current->getData() << " -> ";
            current = current->getNext();
        }
        cout << "nullptr" << endl; // Indicamos el final de la lista
    }

    void pop_front() {
        if(first_ == nullptr) return;
        Node* current = first_;
        first_ = first_->getNext();

        delete current;
        if (first_ == nullptr)
        {
            last_ = nullptr;
        }
    size_--;
    }

    void insert(const T& elem, unsigned int pos) {
        // Si la posición es inválida, no hacemos nada
        if (pos > size_) return;
    
        // Caso especial: insertar en la posición 0 (equivalente a push_front)
        if (pos == 0) {
            push_front(elem);
            return;
        }
    
        // Crear el nuevo nodo
        Node* n = new Node(elem);
        Node* current = first_;
    
        // Avanzamos hasta el nodo anterior a la posición deseada
        for (unsigned int i = 0; i < pos - 1; i++) {
            current = current->getNext();
        }
    
        // Conectamos el nuevo nodo con el siguiente nodo
        n->setNext(current->getNext());
    
        // Hacemos que el nodo anterior apunte al nuevo nodo
        current->setNext(n);
    
        // Si insertamos en la última posición, actualizamos last_
        if (n->getNext() == nullptr) {
            last_ = n;
        }
    
        size_++; // Aumentamos el tamaño de la lista
    }
    

};

// Función principal para probar la lista
int main() {
    List<int> myList;
    
    myList.push_back(10);
    myList.push_back(20);
    myList.push_front(5);
    
    cout << "Lista despues de inserciones: ";
    myList.print(); 

    cout << "Tamaño de la lista: " << myList.size() << endl;

    myList.insert(15, 2);
    myList.print();
    return 0;
}
