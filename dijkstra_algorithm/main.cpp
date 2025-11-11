#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

struct Edge {
    int destination;
    int weight;
};

struct Graph {
    int numberOfNodes;
    vector<vector<Edge>> adjacencyList;

    void initialize(int nodes) {
        numberOfNodes = nodes;
        adjacencyList.resize(nodes);
    }

    void addEdge(int source, int dest, int weight) {
        adjacencyList[source].push_back({dest, weight});
        adjacencyList[dest].push_back({source, weight});
    }
};

struct QueueNode {
    int node;
    int distance;

    bool operator>(const QueueNode &other) const {
        return distance > other.distance;
    }
};

int dijkstra(const Graph &graph, int source, int target) {
    const int INF = numeric_limits<int>::max();
    vector<int> minDistances(graph.numberOfNodes, INF);
    priority_queue<QueueNode, vector<QueueNode>, greater<>> minHeap;

    minDistances[source] = 0;
    minHeap.push({source, 0});

    while (!minHeap.empty()) {
        QueueNode current = minHeap.top();
        minHeap.pop();

        int currentNode = current.node;
        int currentDistance = current.distance;

        if (currentNode == target) {
            return currentDistance;
        }

        if (currentDistance > minDistances[currentNode]) {
            continue;
        }

        for (const Edge &edge : graph.adjacencyList[currentNode]) {
            int neighbor = edge.destination;
            int newDistance = currentDistance + edge.weight;

            if (newDistance < minDistances[neighbor]) {
                minDistances[neighbor] = newDistance;
                minHeap.push({neighbor, newDistance});
            }
        }
    }

    return -1;
}

int main() {
    int testCases;
    cin >> testCases;

    for (int caseNum = 1; caseNum <= testCases; ++caseNum) {
        int numberOfNodes, numberOfEdges, sourceNode, targetNode;
        cin >> numberOfNodes >> numberOfEdges >> sourceNode >> targetNode;

        Graph graph;
        graph.initialize(numberOfNodes);

        for (int i = 0; i < numberOfEdges; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            graph.addEdge(u, v, w);
        }

        int result = dijkstra(graph, sourceNode, targetNode);

        cout << "Case #" << caseNum << ": ";
        if (result == -1) {
            cout << "unreachable" << endl;
        } else {
            cout << result << endl;
        }
    }

    return 0;
}

