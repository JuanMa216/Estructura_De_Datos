#include <iostream>
#include <vector>
#include <random>

using namespace std;

int Partition(vector<int> &v, int LowIndx, int HighIndx) {
    int pivotIndex = (LowIndx + HighIndx) / 2;
    int pivot = v.at(pivotIndex);
    swap(v.at(pivotIndex), v.at(HighIndx)); 
    int i = LowIndx - 1;
    
    for (int j = LowIndx; j < HighIndx; j++) {
        if (v.at(j) <= pivot) {
            i++;
            swap(v.at(i), v.at(j));
        } 
    }
    i++;
    swap(v.at(i), v.at(HighIndx)); 
    
    return i;
}

void QuickSort(vector<int> &v, int LowIndx, int HighIndx) {
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
    cout << "Vector desordenado:" << endl;
    vector<int> b = generateRandomArray(10);

    for (int i = 0; i < b.size(); i++) {
        cout << " " << b.at(i);
    }
    cout << endl;

    QuickSort(b, 0, b.size() - 1);

    cout << "Vector ordenado:" << endl;
    for (int i = 0; i < b.size(); i++) {
        cout << " " << b.at(i);
    }
    cout << endl;

    return 0;
}
