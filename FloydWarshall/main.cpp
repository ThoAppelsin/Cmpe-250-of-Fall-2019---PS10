// C++ Program for Floyd Warshall Algorithm
#include<iostream>

using namespace std;

// Number of vertices in the graph
const int V = 5;

/* Define Infinite as a large enough value. This value will be used  for vertices not connected to each other */

const int INF = 99999;

// A function to print the solution matrix
void printSolution(int dist[][V]);

// Solves the all-pairs shortest path problem using Floyd-Warshall algorithm

void floydWarshall (int graph[][V]) {
    /* dist[][] will be the output matrix that will finally have the shortest distances between every pair of vertices */
    int dist[V][V];

    /* Initialize the solution matrix same as input graph matrix. Or we can say the initial values of shortest distances are based  on shortest paths considering no intermediate vertex. */
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    /* Add all vertices one by one to the set of intermediate vertices. 
        ---> Before start of a iteration, we have shortest distances between all pairs of vertices such that the shortest distances consider only the  vertices in set {0, 1, 2, .. k-1} as intermediate vertices. 
        ----> After the end of a iteration, vertex no. k is added to the set of intermediate vertices and the set becomes {0, 1, 2, .. k} */
    for (int k = 0; k < V; k++) {
        // Pick all vertices as source one by one
        for (int i = 0; i < V; i++) {
            // Pick all vertices as destination for the above picked source
            for (int j = 0; j < V; j++) {
                // If vertex k is on the shortest path from i to j, then update the value of dist[i][j]
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    // Print the shortest distance matrix
    printSolution(dist);
}

/* A utility function to print solution */
void printSolution(int dist[][V]) {
    cout <<"Following matrix shows the shortest distances"
            " between every pair of vertices \n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                cout<< "INF ";
            else
                cout<< dist[i][j]<<" ";
        }
        cout <<endl;
    }
}

// driver program to test above function
int main() {
    int graph[V][V] = {
            { 0 , INF,  6 ,  3 , INF},
            { 3 ,  0 , INF, INF, INF},
            {INF, INF,  0 ,  2 , INF},
            {INF,  1 ,  1 ,  0 , INF},
            {INF,  4 , INF,  2 ,  0 },
    };

    // Print the solution
    floydWarshall(graph);
    return 0;
}

