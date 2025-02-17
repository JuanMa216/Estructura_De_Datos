#include <iostream>
#include <vector>
#include <random>
#include <math.h>
#include <chrono>
#include <fstream>

using namespace std;

void QuickSort(vector<int> *vector, int start, int end, int chose) {
    if (start >= end) return;

    int i = 0, r = 0;
    int pivote = 0;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(start, end);  // Para elegir pivote aleatorio

    if (chose == 1) {
        pivote = vector->at(dist(gen));  // Pivote aleatorio
    } else if (chose == 2) {
        pivote = vector->at((start + end) / 2);
    } else if (chose == 3) {
        pivote = vector->at(end);
    }
    i = start;
    r = end;

    do {
        while (vector->at(i) < pivote) i++;
        while (vector->at(r) > pivote) r--;
        if (i <= r) {
            swap(vector->at(i), vector->at(r));
            i++;
            r--;
        }
    } while (i <= r);

    if (start < r) {
        QuickSort(vector, start, r, chose);
    }
    if (i < end) {
        QuickSort(vector, i, end, chose);
    }
}

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 100);

    int quantity = 0;
    vector<int> variables;

    ofstream tiempos("tiempos.dat", ios::app);
    if (!tiempos) {
        cout << "Error al abrir tiempos.dat\n";
        exit(EXIT_FAILURE);
    }

    auto start = chrono::high_resolution_clock::now();

    // Se redujo el rango de potencias para evitar uso excesivo de memoria
    for (int pot = 2; pot <= 8; pot++) {  // Ahora se usa 10^6 a 10^8 elementos
        quantity = pow(10, pot);
        variables.reserve(quantity);
        tiempos << endl << endl << "Potencia " << pot << endl;

        for (int pivot = 1; pivot <= 3; pivot++) {
            tiempos << endl << "Pivote " << pivot << endl;

            for (int times = 1; times <= 10; times++) {
                variables.clear();
                variables.shrink_to_fit();  // Libera memoria antes de reutilizar el vector

                for (int l = 0; l < quantity; l++) {
                    variables.push_back(dist(gen));
                }

                auto inicio = chrono::high_resolution_clock::now();

                QuickSort(&variables, 0, variables.size() - 1, pivot);

                auto fin = chrono::high_resolution_clock::now();

                auto duracion = chrono::duration_cast<chrono::nanoseconds>(fin - inicio);

                tiempos << times << ".\t" << duracion.count() << endl;
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto totalDuracion = chrono::duration_cast<chrono::milliseconds>(end - start);

    tiempos << endl << "Duracion total en milisegundos: " << totalDuracion.count() << endl;

    return 0;
}
