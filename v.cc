#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

vector<int> generateRandomArray(int size) {

    random_device rd;

    mt19937 gen(rd());

    uniform_int_distribution<> distrib(0, 100);

    vector<int> randomArray(size);

    for (int i = 0; i < size; i++)
    {
        randomArray[i] = distrib(gen);
    }

    return randomArray;
}

int main () {

    cout << "Vector Examples: " << endl;
    vector<int> a;
    cout << "Size: " << a.size() << endl;
    cout << "Vector Examples: " << endl;
    vector<int> b;
    b = generateRandomArray(20);

    for (int i = 0; i < b.size(); i++)
    {
        cout << " " << b.at(i);
    }
    
    cout << " " << endl;

    return 0;
}