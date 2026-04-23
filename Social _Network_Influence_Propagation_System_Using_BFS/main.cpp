#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

template<class Value>
struct Array {
    int n, sz;
    Value* arr;

    void Initialize() {
        n = 0;
        sz = 1;
        arr = new Value[sz];
    }

    void Destroy() {
        delete[] arr;
    }

    void AddLast(Value v) {
        if (n == sz) {
            sz *= 2;
            Value* new_arr = new Value[sz];
            for (int i = 0; i < n; ++i) {
                new_arr[i] = arr[i];
            }
            delete[] arr;
            arr = new_arr;
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

struct Node {
    Array<int> adj;

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
        for (int i = 0; i < n; ++i) {
            nodes[i].Initialize();
        }
    }

    void Destroy() {
        for (int i = 0; i < n; ++i) {
            nodes[i].Destroy();
        }
        delete[] nodes;
    }
};

template<class Type>
struct Queue {
    int f, b, sz, n;
    Type* elems;

    void Initialize(int size) {
        f = n = 0;
        sz = size;
        b = size - 1;
        elems = new Type[sz];
    }

    void Destroy() {
        delete[] elems;
    }

    void Add(Type t) {
        b = (b + 1) % sz;
        elems[b] = t;
        n++;
    }

    Type Pop() {
        Type elem = elems[f];
        f = (f + 1) % sz;
        n--;
        return elem;
    }

    Type Peek() {
        return elems[f];
    }

    int Num() {
        return n;
    }
};

int main() {
    int E;
    cin >> E;
    Graph graph;
    graph.Initialize(E);

    for (int i = 0; i < E; ++i) {
        int N;
        cin >> N;
        for (int j = 0; j < N; ++j) {
            int friend_id;
            cin >> friend_id;
            graph.nodes[i].adj.AddLast(friend_id);
        }
    }

    int T;
    cin >> T;
    while (T--) {
        int source;
        cin >> source;

        vector<bool> visited(E, false);
        Queue<int> q;
        q.Initialize(E);
        q.Add(source);
        visited[source] = true;

        vector<int> day_count(E, 0);
        vector<int> boom_size(E, 0);

        while (q.Num() > 0) {
            int u = q.Pop();
            for (int i = 0; i < graph.nodes[u].adj.n; ++i) {
                int v = graph.nodes[u].adj[i];
                if (!visited[v]) {
                    visited[v] = true;
                    q.Add(v);
                    day_count[v] = day_count[u] + 1;
                    boom_size[day_count[v]]++;
                }
            }
        }

        int max_boom_size = 0;
        int first_boom_day = 0;
        for (int i = 0; i < E; ++i) {
            if (boom_size[i] > max_boom_size) {
                max_boom_size = boom_size[i];
                first_boom_day = i;
            }
        }

        if (max_boom_size == 0) {
            cout << 0 << endl;
        } else {
            cout << max_boom_size << " " << first_boom_day << endl;
        }

        q.Destroy();
    }

    graph.Destroy();
    return 0;
}
