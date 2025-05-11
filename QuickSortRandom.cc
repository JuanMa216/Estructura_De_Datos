#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>

using namespace std;
using namespace chrono; // Para medir el tiempo

// Función para generar un vector aleatorio de tamaño 'size'
void RandomVector(vector<int>& v, int size, long int range) {
    random_device rd;
    mt19937 gen(rd()); // Generador de números aleatorios
    uniform_int_distribution<> distrib(0, range); // Rango de valores aleatorios

    v.clear();      // Asegura que el vector esté vacío antes de llenarlo
    v.reserve(size); // Reserva espacio para evitar realocaciones

    for (int i = 0; i < size; i++) {
        v.push_back(distrib(gen));
    }
}

// Función de partición para QuickSort
int Partition(vector<int>& v, int low, int high) {
    int pivot = v[high], i = low;
    for (int j = low; j <= high - 1; j++) {
        if (v[j] <= pivot) {
            swap(v[i], v[j]);
            i++;
        }
    }
    swap(v[i], v[high]);
    return i;
}

// Función para seleccionar un pivote aleatorio y particionar
int Random_Indx(vector<int>& v, int low, int high) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(low, high);
    int pivot = distrib(gen);
    swap(v[pivot], v[high]);
    return Partition(v, low, high);
}

// Implementación de QuickSort con pivote aleatorio
void QuickSortRandom(vector<int>& v, int Low, int High) {
    if (Low < High) {
        int pivotIndx = Random_Indx(v, Low, High);
        QuickSortRandom(v, Low, pivotIndx - 1);
        QuickSortRandom(v, pivotIndx + 1, High);
    }
}

int main() {
    int size = pow(10,8); 
    long int range = pow(10, 10); 
    int num_tests = 10; 
    vector<int> original;  // Vector original
    RandomVector(original, size, range);  

    for (int i = 0; i < num_tests; i++) {
        vector<int> test_vector = original;  // Copiar el vector original para cada prueba

        auto start = high_resolution_clock::now();  // Iniciar medición
        QuickSortRandom(test_vector, 0, test_vector.size() - 1);
        auto end = high_resolution_clock::now();  // Terminar medición

        double duration = duration_cast<nanoseconds>(end - start).count() / 1e9; // Segundos
        cout << "Prueba " << i + 1 << ": " << duration << " s" << endl;
    }

    return 0;
}
