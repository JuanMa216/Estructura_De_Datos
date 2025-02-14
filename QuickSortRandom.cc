#include <iostream>
#include <vector>
#include <random>

using namespace std;

int Partition(vector<int>* v, int low, int high) {
    int pivot = v->at(high), i = low;

    for (int j = low; j <= high  - 1; j++)
    {
        if (v->at(j) <= pivot)
        {
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

void RandomVector (vector<int>* v, int i, int size) {
    if (i < size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 100);

    v->push_back(distrib(gen));
    RandomVector(v, i + 1, size);
    }
}


int main() {
    cout << "QuickSort with a random pivot" << endl;
    vector<int> b;
    cout << "Vector not sorted: " << endl;
    RandomVector(&b, 0, 10);

    for (int i = 0; i < b.size(); i++)
    {
        cout << " " << b.at(i);
    }
    cout << endl;

    cout << "Vector after being sorted: " << endl;
    QuickSortRandom(&b, 0, b.size() - 1);
    for (int i = 0; i < b.size(); i++)
    {
        cout << " " << b.at(i);
    }
    cout << endl;

    return 0;
}