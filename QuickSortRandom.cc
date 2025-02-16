#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <chrono> // Librería para medir tiempo

using namespace std;
using namespace chrono; // Para simplificar la sintaxis

int Partition(vector<int>* v, int low, int high) {
    int pivot = v->at(high), i = low;

    for (int j = low; j <= high - 1; j++) {
        if (v->at(j) <= pivot) {
            swap(v->at(i), v->at(j));
            i++;
        }
    }
    swap(v->at(i), v->at(high));
    return i;
}

int Random_Indx(vector<int>* v, int low, int high) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(low, high);
    int pivot = distrib(gen);
    swap(v->at(pivot), v->at(high));
    return Partition(v, low, high);
}

void QuickSortRandom(vector<int>* v, int Low, int High) {
    if (Low < High) {
        int pivotIndx = Random_Indx(v, Low, High);
        QuickSortRandom(v, Low, pivotIndx - 1);
        QuickSortRandom(v, pivotIndx + 1, High);
    }
}

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
    cout << "QuickSort with a random pivot" << endl;
    vector<int> b;
    int size = pow(10, 2); // 

    cout << "Generating random vector..." << endl;
    RandomVector(&b, size);

    cout << "Sorting with QuickSort..." << endl;
    auto start = high_resolution_clock::now(); // Inicio del cronómetro

    QuickSortRandom(&b, 0, b.size() - 1);

    auto end = high_resolution_clock::now(); // Fin del cronómetro
    double duration = duration_cast<milliseconds>(end - start).count(); // Convertir a ms

    cout << "Sorting completed in " << duration << " ms." << endl;

    return 0;
}
