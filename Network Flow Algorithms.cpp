#include <bits/stdc++.h>


using namespace std;
/*
UserId=Moinul
Password=Moinul909
*/
const string USER_ID = "Moinul";
const string PASSWORD = "Moinul909";

#define V 6  // Number of vertices in the graph

// ========== Login Function ==========
bool login() {
    string userId, password;
    cout << "Enter User ID: ";
    cin >> userId;
    cout << "Enter Password: ";
    cin >> password;

    if (userId == USER_ID && password == PASSWORD) {
        cout << "Login successful!\n";
        return true;
    } else {
        cout << "Login failed. Incorrect User ID or Password.\n";
        return false;
    }
}

// ========== Breadth-First Search to find augmenting path ==========
bool bfs(int residualGraph[V][V], int source, int sink, int parent[]) {
    bool visited[V];
    memset(visited, 0, sizeof(visited));

    queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            if (!visited[v] && residualGraph[u][v] > 0) {
                if (v == sink) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return false;
}

// ========== Ford-Fulkerson Algorithm (Edmonds-Karp approach) ==========
int fordFulkerson(int graph[V][V], int source, int sink) {
    int u, v;

    // Create a residual graph and fill it with given capacities in the original graph
    int residualGraph[V][V];
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            residualGraph[u][v] = graph[u][v];

    int parent[V];  // Array to store the augmenting path
    int max_flow = 0;  // There is no flow initially

    // Augment the flow while there is a path from source to sink
    while (bfs(residualGraph, source, sink, parent)) {
        int path_flow = INT_MAX;

        // Find the maximum flow through the path found by BFS
        for (v = sink; v != source; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, residualGraph[u][v]);
        }

        // Update the residual capacities of the edges and reverse edges
        for (v = sink; v != source; v = parent[v]) {
            u = parent[v];
            residualGraph[u][v] -= path_flow;
            residualGraph[v][u] += path_flow;
        }

        // Add the path flow to the overall flow
        max_flow += path_flow;
    }

    return max_flow;
}

// ========== Display Graph ==========
void displayGraph(int graph[V][V]) {
    cout << "Graph adjacency matrix (capacities between nodes):\n";
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
}

// ========== Main Program ==========
int main() {
    if (!login()) {
        return 0;
    }

    // Graph representation with capacity between each pair of vertices
    int graph[V][V] = {
        {0, 16, 13, 0, 0, 0},
        {0, 0, 10, 12, 0, 0},
        {0, 4, 0, 0, 14, 0},
        {0, 0, 9, 0, 0, 20},
        {0, 0, 0, 7, 0, 4},
        {0, 0, 0, 0, 0, 0}
    };

    displayGraph(graph);

    int source = 0;  // Source node
    int sink = 5;    // Sink node

    cout << "\nThe maximum possible flow is: " << fordFulkerson(graph, source, sink) << endl;

    return 0;
}

