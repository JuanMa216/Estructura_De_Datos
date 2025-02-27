#include <iostream>

using namespace std;
template <typename T>

class DLList {
    private:
        class Node {
        public:
            T x;
            Node *prev, *next;
        };
    
        Node dummy;  // Nodo centinela
        int n;       // Tamaño de la lista
    
    public:
        DLList() {
            dummy.next = &dummy;  // El siguiente del dummy es él mismo
            dummy.prev = &dummy;  // El anterior del dummy es él mismo
            n = 0;               // La lista empieza vacía
        }

        Node* getNode(int i) {
            Node* p;
        
            // Caso 1: Si 'i' se encuentra en la primera mitad de la lista (Cerca de head).
            if (i < n / 2) {
                p = dummy.next; // Empezamos desde el primer nodo real (el siguiente al nodo dummy).
                for (int j = 0; j < i; j++) // Recorremos la lista hacia adelante.
                    p = p->next; // Avanzamos al siguiente nodo.
            } 
            // Caso 2: Si 'i' se encuentra en la segunda mitad de la lista (Cerca de tail).
            else {
                p = &dummy; // Empezamos desde el nodo dummy (final de la lista en listas circulares).
                for (int j = n; j > i; j--) 
                    p = p->prev; // Retrocedemos al nodo anterior.
            }
        
            return p; // Retornamos el nodo en la posición 'i'.
        }
        
        

    };
    