#include <iostream>
#include <vector>
#include <random>

using namespace std;

void Merge(vector<int>* L, vector<int>* R, vector<int>* A) {
    
    int nL = L->size(), nR = R->size(), i = 0, j = 0, k = 0;

    while (i < nL && j < nR)
    {
        if (L->at(i) <= R->at(j))
        {
            A->at(k) = L->at(i);
            i++; 
        } else {
            A->at(k) = R->at(j);
            j++;
        }
    k++;
    }

    while (i < nL)
    {
        A->at(k) = L->at(i);
        i++;
        k++;
    }

    while (j < nR)
    {
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

    for (int i = 0; i < mid; i++)
    {
        left.at(i) = v->at(i);
    }

    for (int j = mid; j < size; j++)
    {
        right.at(j-mid) = v->at(j);
    }

    MergeSort(&left);
    MergeSort(&right);
    Merge(&left, &right, v);
    
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
    cout << "Merge Sort Algorithm." << endl;
    cout << "Vector not sorted:" << endl;
    vector<int> b;
    RandomVector(&b, 0, 10);

    for (int i = 0; i < b.size(); i++)
    {
        cout << " " << b.at(i);
    }
    cout << endl;

    cout << "Vector after being sorted: " << endl;
    MergeSort(&b);
    
    for (int i = 0; i < b.size(); i++)
    {
        cout << " " << b.at(i);
    }
    cout << endl;

    return 0;
}