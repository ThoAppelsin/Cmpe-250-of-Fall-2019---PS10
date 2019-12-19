#include <iostream>

// C++ program for Bellman-Ford's single source
// shortest path algorithm.

#include <iostream>
#include <stack>
#include <climits>

using namespace std;

// a structure to represent a weighted edge in graph
struct Edge {
    int src, dest, weight;
};

// a class to represent a connected, directed and
// weighted graph
class Graph {
    // V-> Number of vertices, E-> Number of edges
    int V, E;

    // graph is represented as an array of edges.
    struct Edge* edge;
    // Creates a graph with V vertices and E edges

public:
    Graph(int V, int E) {
        this->V = V;
        this->E = E;
        edge = new struct Edge[E];
    }
    ~Graph() {
        delete[] edge;
    }
    void addEdge(int E, int src, int dest, int weight) {
        edge[E].src = src;
        edge[E].dest = dest;
        edge[E].weight = weight;

    }
    struct Edge getEdge(int E) {
        return edge[E];
    }
    int getNumVertex() {
        return V;
    }
    int getNumEdge() {
        return E;
    }

};

// A utility function used to print the solution
void printArr(int dist[], int predecessor[], int src, int n) {

    cout << "Vertex  Distance from Source Shortest Path\n";
    for (int i = 0; i < n; ++i) {
        cout << " " << i << "          ";
        if (dist[i] != INT_MAX)
            cout << dist[i];
        else
            cout << "INF";

        cout << "                  ";

        int u = i;
        stack<int> predStack;
        if (dist[u] != INT_MAX && u != src) {

            do {
                u = predecessor[u];
                predStack.push(u);

            } while (u != src);
        }

        //print in reverse

        while (!predStack.empty()) {
            cout << " " << predStack.top();
            predStack.pop();
        }
        cout << endl;

    }
}


// The function that finds shortest distances from src to
// all other vertices using Bellman-Ford algorithm.  The function
// also detects negative weight cycle
void BellmanFord(Graph graph, int src) {
    int V = graph.getNumVertex();
    int E = graph.getNumEdge();
    int dist[V], predecessor[V];
    struct Edge theEdge;
    // Step 1: Initialize distances from src to all other vertices
    // as INFINITE
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        predecessor[i] = -1;
    }
    dist[src] = 0;

    // Step 2: Relax all edges |V| - 1 times. A simple shortest
    // path from src to any other vertex can have at-most |V| - 1
    // edges
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            theEdge = graph.getEdge(j);
            int u = theEdge.src;
            int v = theEdge.dest;
            int weight = theEdge.weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                predecessor[v] = u;

            }
        }
    }

    // Step 3: check for negative-weight cycles.  The above step
    // guarantees shortest distances if graph doesn't contain
    // negative weight cycle.  If we get a shorter path, then there
    // is a cycle.
    for (int i = 0; i < E; i++) {
        theEdge = graph.getEdge(i);
        int u = theEdge.src;
        int v = theEdge.dest;
        int weight = theEdge.weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
            cout << "Graph contains negative weight cycle\n";
    }

    printArr(dist, predecessor, src, V);

    return;
}

int main() {


    int V = 5;  // Number of vertices in graph
    int E = 8;  // Number of edges in graph
    Graph graph(V, E);

    graph.addEdge(0, 0, 2, 6);
    graph.addEdge(1, 2, 3, 2);
    graph.addEdge(2, 3, 2, 1);
    graph.addEdge(3, 0, 3, 3);
    graph.addEdge(4, 3, 1, 1);
    graph.addEdge(5, 4, 3, 2);
    graph.addEdge(6, 1, 0, 3);
    graph.addEdge(7, 4, 1, 4);

    BellmanFord(graph, 4);

    return 0;
}


