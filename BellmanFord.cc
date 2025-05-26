#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
#include <cassert>
using namespace std;

const int INF = numeric_limits<int>::max();
typedef vector<vector<int>> Matrix;

class Graph
{
private:
    Matrix adj_matrix;
    Matrix edge_list;

    void print_matrix(const Matrix &matrix)
    {
        int n = adj_matrix.size();
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (adj_matrix[i][j] == INF)
                    cout << setw(5) << "∞";
                else
                    cout << setw(3) << adj_matrix[i][j];
            }
            cout << endl;
        }
    }

    vector<int> soluton(int V, Matrix &edges, int S)
    {
        vector<int> dist(V, INF);
        dist[S] = 0;
        for (int i = 0; i < V - 1; i++)
        {
            for (auto it : edges)
            {
                int u = it[0];
                int v = it[1];
                int wt = it[2];
                if (dist[u] != INF && dist[u] + wt < dist[v])
                    dist[v] = dist[u] + wt;
            }
        }

        return dist;
    }

public:
    Graph(int n, const Matrix &adj_list)
    {
        adj_matrix = Matrix(n, vector<int>(n, INF));
        edge_list = adj_list;

        for (const auto &edge : adj_list)
        {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            if (u != v)
            {
                adj_matrix[u][v] = w;
            }
        }
    }

    void print_adj_matrix()
    {
        cout << "Matriz de adyacencia (pesos):\n";
        print_matrix(adj_matrix);
    }

    void BellmanFord(int source, int nodes)
    {
        assert(source >= 0 && source < nodes);
        vector<int> result = soluton(nodes, edge_list, source);
        cout << "Vector de distancias minimas desde " << source << " :" << endl;
        for (auto &elem : result)
        {
            if (elem == INF)
                cout << ". ";
            else
                cout << elem << " ";
        }
        cout << endl;
    }
};

int main()
{
    int Nodes = 6;
    Matrix adj_list = {
        {3, 2, 6}, {5, 3, 1}, {0, 1, 5}, {1, 5, -3}, {1, 2, -1}, {3, 4, -2}, {2, 4, 3}};

    Graph graph(Nodes, adj_list);
    graph.print_adj_matrix();
    graph.BellmanFord(0, Nodes);
    return 0;
}
