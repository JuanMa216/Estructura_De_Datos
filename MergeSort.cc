#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>

using namespace std;
using namespace chrono;

void Merge(vector<int>* L, vector<int>* R, vector<int>* A) {
    int nL = L->size(), nR = R->size(), i = 0, j = 0, k = 0;

    while (i < nL && j < nR) {
        if (L->at(i) <= R->at(j)) {
            A->at(k) = L->at(i);
            i++; 
        } else {
            A->at(k) = R->at(j);
            j++;
        }
        k++;
    }

    while (i < nL) {
        A->at(k) = L->at(i);
        i++;
        k++;
    }

    while (j < nR) {
        A->at(k) = R->at(j);
        j++;
        k++;
    }
}

void MergeSort(vector<int>* v) {
    int size = v->size();
    if (size < 2) return;

    int mid = size / 2;
    vector<int> left(mid);
    vector<int> right(size - mid);

    for (int i = 0; i < mid; i++) {
        left.at(i) = v->at(i);
    }
    for (int j = mid; j < size; j++) {
        right.at(j - mid) = v->at(j);
    }

    MergeSort(&left);
    MergeSort(&right);
    Merge(&left, &right, v);
}

void RandomVector(vector<int>* v, int size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 100);
    v->clear();
    v->reserve(size);

    for (int i = 0; i < size; i++) {
        v->push_back(distrib(gen));
    }
}

int main() {
    int size = pow(10,9); // Tamaño del vector
    int num_tests = 10;
    vector<int> original;
    RandomVector(&original, size);

    for (int i = 0; i < num_tests; i++) {
        vector<int> test_vector = original;
        auto start = high_resolution_clock::now();
        MergeSort(&test_vector);
        auto end = high_resolution_clock::now();

        double duration = duration_cast<nanoseconds>(end - start).count() / 1e9; // Segundos
        cout << "Prueba " << i + 1 << ": " << duration << " s" << endl;
    }
    return 0;
}
