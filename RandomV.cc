#include <iostream>
#include <vector>
#include <random>
#include <cmath>

using namespace std;

void RandomVector(vector<int>* v, int size) {
    random_device rd;
    mt19937 gen(rd()); // Generador de números aleatorios
    uniform_int_distribution<> distrib(0, 100); // Rango de valores aleatorios

    v->clear(); // Asegura que el vector esté vacío antes de llenarlo
    v->reserve(size); // Reserva espacio para evitar realocaciones

    for (int i = 0; i < size; i++) {
        v->push_back(distrib(gen));
    }
}

int main() {
    cout << "Generating random vector..." << endl;
    vector<int> b;
    int size = pow(10, 2);
    RandomVector(&b, size);
    
    for (int i = 0; i < size; i++)
    {
        cout << " " << b.at(i);
    }
    cout << endl;

    return 0;
}