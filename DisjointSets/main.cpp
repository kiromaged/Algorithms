#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

struct DisjointSets {
    int n;
    int* parent;
    int* num_nodes;

    void Initialize(int _n) {
        n = _n;
        parent = new int[n];
        num_nodes = new int[n];
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            num_nodes[i] = 1;
        }
    }

    void Destroy() {
        delete[] parent;
        delete[] num_nodes;
    }

    int Find(int i) {
        if (parent[i] != i) {
            parent[i] = Find(parent[i]); // Path compression
        }
        return parent[i];
    }

    bool Union(int i, int j) {
        int root_i = Find(i);
        int root_j = Find(j);
        if (root_i != root_j) {
            // Union by size
            if (num_nodes[root_i] > num_nodes[root_j]) {
                parent[root_j] = root_i;
                num_nodes[root_i] += num_nodes[root_j];
            } else {
                parent[root_i] = root_j;
                num_nodes[root_j] += num_nodes[root_i];
            }
            return true;
        }
        return false;
    }
};

int main() {
    int t;
    cin >> t;
    while (t--) {
        int N, M;
        cin >> N >> M;
        DisjointSets ds;
        ds.Initialize(N);

        for (int i = 0; i < M; ++i) {
            int A, B;
            cin >> A >> B;
            ds.Union(A-1, B-1);
        }

        int max_group_size = 0;
        for (int i = 0; i < N; ++i) {
            int root = ds.Find(i);
            if (ds.num_nodes[root] > max_group_size) {
                max_group_size = ds.num_nodes[root];
            }
        }

        cout << max_group_size << endl;
        ds.Destroy();
    }
    return 0;
}
