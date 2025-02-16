#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>

using namespace std;
using namespace chrono;

int Partition(vector<int>& v, int LowIndx, int HighIndx) {
    int pivot = v[HighIndx]; // Ahora el pivote es el último elemento
    int i = LowIndx - 1;
    
    for (int j = LowIndx; j < HighIndx; j++) {
        if (v[j] <= pivot) {
            i++;
            swap(v[i], v[j]);
        } 
    }
    i++;
    swap(v[i], v[HighIndx]); 
    
    return i;
}

void QuickSort(vector<int>& v, int LowIndx, int HighIndx) {
    if (HighIndx <= LowIndx) return;
    int pivot = Partition(v, LowIndx, HighIndx);
    QuickSort(v, LowIndx, pivot - 1);
    QuickSort(v, pivot + 1, HighIndx);
}

vector<int> generateRandomArray(int size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 100);
    
    vector<int> randomArray(size);
    for (int i = 0; i < size; i++) {
        randomArray[i] = distrib(gen);
    }
    return randomArray;
}

int main() {
    int size = pow(10,7);  // Tamaño del vector
    int tests = 10;  // Cantidad de pruebas con el mismo vector
    
    vector<int> b = generateRandomArray(size);
    
    //cout << "Vector desordenado:" << endl;
    //for (int num : b) {
    //    cout << " " << num;
    //}
    //cout << endl;
    
    for (int i = 0; i < tests; i++) {
        vector<int> copy = b; // Copia del vector original para cada prueba
        auto start = high_resolution_clock::now();
        QuickSort(copy, 0, copy.size() - 1);
        auto end = high_resolution_clock::now();
        
        // Medir tiempo en nanosegundos
        long long duration_ns = duration_cast<nanoseconds>(end - start).count();
        // Convertir a segundos
        double duration_sec = duration_ns * 1e-9;

        cout << "Prueba " << i + 1 << ": " << duration_ns << " ns (" 
             << duration_sec << " s)" << endl;
    }
    
    return 0;
}
