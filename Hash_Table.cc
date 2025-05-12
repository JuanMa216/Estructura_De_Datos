#include <iostream>
#include <vector>
#include <list>

using namespace std;

template <class T>
class HashTable
{
private:
  vector<list<T>> table;
  int total_elements;

  // Hash function (genérica para tipos numéricos y strings simples)
  int getHash(const T &key)
  {
    return key % total_elements;
  }

public:
  // Constructor
  HashTable(int n)
  {
    total_elements = n;
    table.resize(total_elements);
  }

  // Insertar elemento (sin duplicados)
  void insertElement(const T &key)
  {
    int index = getHash(key);
    for (const T &val : table[index])
    {
      if (val == key)
        return; // Ya existe
    }
    table[index].push_back(key);
  }

  // Eliminar elemento
  void removeElement(const T &key)
  {
    int index = getHash(key);
    table[index].remove(key); // remove elimina todas las ocurrencias
  }

  // Buscar elemento
  bool searchElement(const T &key)
  {
    int index = getHash(key);
    for (const T &val : table[index])
    {
      if (val == key)
        return true;
    }
    return false;
  }

  // Imprimir la tabla
  void printAll()
  {
    for (int i = 0; i < total_elements; i++)
    {
      cout << "Index " << i << ": ";
      for (const T &val : table[i])
      {
        cout << val << " => ";
      }
      cout << endl;
    }
  }
};

// Main de prueba
int main()
{
  HashTable<int> ht(3);
  cout << alumno1.edad << endl;
  int arr[] = {2, 4, 6, 8, 10};

  for (int i = 0; i < 5; i++)
    ht.insertElement(arr[i]);

  cout << "..:: Hash Table ::.." << endl;
  ht.printAll();

  ht.removeElement(4);
  cout << endl
       << "..:: After deleting 4 ::.." << endl;
  ht.printAll();

  return 0;
}
