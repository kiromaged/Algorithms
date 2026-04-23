#include <iostream>
#include <fstream>
#include <vector>

const int MAX_COST = 10000;

struct Node {
    char label;
    int cost;
    Node(char l = 'A', int c = MAX_COST) : label(l), cost(c) {}
};

struct MinHeap {
    std::vector<Node> heap;
    void insert(Node node);
    Node extractMin();
    bool isEmpty() const { return heap.empty(); }

    // Helper function to maintain the heap property
    void heapifyUp(int index);
    void heapifyDown(int index);
};

void MinHeap::insert(Node node) {
    heap.push_back(node);
    heapifyUp(heap.size() - 1);
}

Node MinHeap::extractMin() {
    if (heap.empty()) {
        return Node(); // Return a default Node with max cost
    }
    Node minNode = heap.front();
    std::swap(heap.front(), heap.back());
    heap.pop_back();
    if (!heap.empty()) {
        heapifyDown(0);
    }
    return minNode;
}

void MinHeap::heapifyUp(int index) {
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        if (heap[parentIndex].cost > heap[index].cost) {
            std::swap(heap[parentIndex], heap[index]);
            index = parentIndex;
        } else {
            break;
        }
    }
}

void MinHeap::heapifyDown(int index) {
    int leftChildIndex = 2 * index + 1;
    int rightChildIndex = 2 * index + 2;
    int smallestIndex = index;
    if (leftChildIndex < heap.size() && heap[leftChildIndex].cost < heap[smallestIndex].cost) {
        smallestIndex = leftChildIndex;
    }
    if (rightChildIndex < heap.size() && heap[rightChildIndex].cost < heap[smallestIndex].cost) {
        smallestIndex = rightChildIndex;
    }
    if (smallestIndex != index) {
        std::swap(heap[index], heap[smallestIndex]);
        heapifyDown(smallestIndex);
    }
}


class WeightedGraph {
    std::vector<std::vector<int>> g;
    int nVertices;
public:
    int getNVertices();
    int getWeight(char, char);
    std::vector<int> returnNeighbors(int v);
    int numNeighbors(int v);
    void loadGraphFromFile(std::ifstream&);
    void dijkstra(char startVertex, char* prev, Node distances[]);
    ~WeightedGraph() {}
};

int WeightedGraph::getNVertices() {
    return nVertices;
}

int WeightedGraph::getWeight(char v1, char v2) {
    return g[v1 - 'A'][v2 - 'A'];
}

std::vector<int> WeightedGraph::returnNeighbors(int v) {
    std::vector<int> neighbors;
    for (int i = 0; i < nVertices; ++i) {
        if (g[v][i] > 0) {
            neighbors.push_back(i);
        }
    }
    return neighbors;
}

int WeightedGraph::numNeighbors(int v) {
    int count = 0;
    for (int i = 0; i < nVertices; ++i) {
        if (g[v][i] > 0) {
            ++count;
        }
    }
    return count;
}

void WeightedGraph::loadGraphFromFile(std::ifstream& file) {
    file >> nVertices;
    g.resize(nVertices, std::vector<int>(nVertices, 0));
    int edges;
    file >> edges;
    for (int i = 0; i < edges; i++) {
        char v1, v2;
        int weight;
        file >> v1 >> v2 >> weight;
        g[v1 - 'A'][v2 - 'A'] = weight;
    }
}

void WeightedGraph::dijkstra(char startVertex, char* prev, Node distances[]) {
    MinHeap minHeap;
    distances[startVertex - 'A'].cost = 0;
    minHeap.insert(distances[startVertex - 'A']);
    while (!minHeap.isEmpty()) {
        Node u = minHeap.extractMin();
        std::vector<int> neighbors = returnNeighbors(u.label - 'A');
        for (int v : neighbors) {
            int alt = distances[u.label - 'A'].cost + getWeight(u.label, v + 'A');
            if (alt < distances[v].cost) {
                distances[v].cost = alt;
                prev[v] = u.label;
                // Check if the node is already in the minHeap
                bool inHeap = false;
                // Convert char to int before comparison
                char v_char = v + 'A';
                for (auto& node : minHeap.heap) {
                    if (node.label == v_char) {
                        inHeap = true;
                        break;
                    }
                }
                if (!inHeap) {
                    minHeap.insert(Node(v_char, alt));
                }
            }
        }
    }
}

int main() {
    std::ifstream file("graph.txt");
    if (!file) {
        std::cerr << "Unable to open file";
        return 1;
    }

    WeightedGraph graph;
    graph.loadGraphFromFile(file);
    file.close();

    int n = graph.getNVertices();
    Node* distances = new Node[n];
    for (int i = 0; i < n; ++i) {
        distances[i].label = 'A' + i;
    }
    char* prev = new char[n];
    for (int i = 0; i < n; ++i) {
        prev[i] = 0;
    }

    graph.dijkstra('G', prev, distances);

    std::cout << "Node\tCost\tPrevious" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << distances[i].label << "\t";
        if (distances[i].cost == MAX_COST) {
            std::cout << "INF\t";
        }
        else {
            std::cout << distances[i].cost << "\t";
        }
        if (prev[i] == 0 && distances[i].label != 'G') {
            std::cout << "-" << std::endl;
        }
        else {
            std::cout << prev[i] << std::endl;
        }
    }

    delete[] distances;
    delete[] prev;

    return 0;
}
