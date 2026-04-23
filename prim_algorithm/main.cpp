#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <iomanip>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Value>
struct Array {
    int n, sz;
    Value* arr;

    void Initialize() {
        n = 0;
        sz = 2;
        arr = new Value[sz];
    }

    void Destroy() {
        delete[] arr;
    }

    void AddLast(Value v) {
        if (n == sz) {
            sz *= 2;
            Value* newArr = new Value[sz];
            for (int i = 0; i < n; i++) newArr[i] = arr[i];
            delete[] arr;
            arr = newArr;
        }
        arr[n++] = v;
    }

    void RemoveLast() {
        if (n > 0) n--;
    }

    Value& operator[](int i) {
        return arr[i];
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge {
    int v;         // id of the adjacent node
    double w;      // edge weight = distance between the two nodes
};

struct Node {
    int x, y;      // x and y coordinates of the node
    Array<Edge> adj;

    void Initialize() {
        adj.Initialize();
    }

    void Destroy() {
        adj.Destroy();
    }
};

struct Graph {
    int n;
    Node* nodes;

    void Initialize(int _n) {
        n = _n;
        nodes = new Node[n];
        for (int i = 0; i < n; i++) nodes[i].Initialize();
    }

    void Destroy() {
        for (int i = 0; i < n; i++) nodes[i].Destroy();
        delete[] nodes;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Find the square root of "v" in "n" iterations (optional, as <cmath> sqrt is fine)
double Sqrt(double v, int n=100) {
    return sqrt(v);
}

// Calculate Euclidean distance between two nodes
double distance(int x1, int y1, int x2, int y2) {
    return Sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

double primMinimax(Graph& g, int start, int end) {
    vector<double> maxEdge(g.n, 1e9);
    vector<bool> visited(g.n, false);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;

    maxEdge[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        double maxDist = pq.top().first;
        pq.pop();

        if (u == end) return maxDist;
        if (visited[u]) continue;
        visited[u] = true;

        for (int i = 0; i < g.nodes[u].adj.n; i++) {
            Edge& e = g.nodes[u].adj[i];
            if (!visited[e.v]) {
                double newDist = max(maxDist, e.w);
                if (newDist < maxEdge[e.v]) {
                    maxEdge[e.v] = newDist;
                    pq.push({newDist, e.v});
                }
            }
        }
    }
    return -1; // unreachable case (shouldn't happen in valid input)
}

int main() {
    int testCase = 1;
    while (true) {
        int n;
        cin >> n;
        if (n == 0) break;

        Graph g;
        g.Initialize(n);

        // Read nodes (stones) coordinates
        for (int i = 0; i < n; i++) {
            cin >> g.nodes[i].x >> g.nodes[i].y;
        }

        // Build graph with distances as weights
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                double dist = distance(g.nodes[i].x, g.nodes[i].y, g.nodes[j].x, g.nodes[j].y);
                g.nodes[i].adj.AddLast({j, dist});
                g.nodes[j].adj.AddLast({i, dist});
            }
        }

        // Run Prim's algorithm to find the minimax path from node 0 (Freddy) to node 1 (Fiona)
        double frogDistance = primMinimax(g, 0, 1);

        // Output result
        cout << "Scenario #" << testCase++ << endl;
        cout << "Frog Distance = " << fixed << setprecision(3) << frogDistance << endl;
        cout << endl;

        g.Destroy();
    }
    return 0;
}
