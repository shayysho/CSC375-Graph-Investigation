#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

// Structure to hold our graph representations
struct Graph {
    int numNodes;
    vector<vector<int>> adjList;
    vector<vector<int>> adjMatrix; // 2D grid of 0s and 1s
};

// Function to generate a random test graph
Graph createGraph(int numNodes, double edgeProb) {
    Graph g;
    g.numNodes = numNodes;
    g.adjList.resize(numNodes);
    
    // Create a 2D matrix initialized with 0s
    g.adjMatrix = vector<vector<int>>(numNodes, vector<int>(numNodes, 0));

    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            if (i != j) {
                // Random probability check for adding an edge
                double randomVal = (double)rand() / RAND_MAX;
                if (randomVal < edgeProb) {
                    g.adjList[i].push_back(j);
                    g.adjMatrix[i][j] = 1;
                }
            }
        }
    }
    return g;
}

// Breadth-First Search using Adjacency List
void bfsList(const Graph& g, int startNode) {
    vector<bool> visited(g.numNodes, false);
    queue<int> q;

    visited[startNode] = true;
    q.push(startNode);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor : g.adjList[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

// Breadth-First Search using Adjacency Matrix
void bfsMatrix(const Graph& g, int startNode) {
    vector<bool> visited(g.numNodes, false);
    queue<int> q;

    visited[startNode] = true;
    q.push(startNode);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor = 0; neighbor < g.numNodes; neighbor++) {
            if (g.adjMatrix[current][neighbor] == 1 && !visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    srand(time(0)); // Seed random number generator

    vector<int> testSizes = {100, 500, 1000, 2500};
    double edgeProbability = 0.05;

    cout << "CSC 375 - Graph Search Performance Results" << endl;
    cout << "------------------------------------------" << endl;
    cout << "Nodes\tList BFS (ms)\tMatrix BFS (ms)" << endl;

    for (int n : testSizes) {
        Graph g = createGraph(n, edgeProbability);

        // Time Adjacency List BFS
        auto startList = chrono::high_resolution_clock::now();
        for (int i = 0; i < 10; i++) {
            bfsList(g, 0);
        }
        auto endList = chrono::high_resolution_clock::now();
        double listTime = chrono::duration<double, milli>(endList - startList).count() / 10.0;

        // Time Adjacency Matrix BFS
        auto startMatrix = chrono::high_resolution_clock::now();
        for (int i = 0; i < 10; i++) {
            bfsMatrix(g, 0);
        }
        auto endMatrix = chrono::high_resolution_clock::now();
        double matrixTime = chrono::duration<double, milli>(endMatrix - startMatrix).count() / 10.0;

        cout << n << "\t" << listTime << " ms\t\t" << matrixTime << " ms" << endl;
    }

    return 0;
}