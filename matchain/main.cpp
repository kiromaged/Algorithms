#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int p[11]; // the dimensions of matrices

int T[11][11]; // T[a][b]=the optimal number of multiplication of p[a]...p[b]
int D[11][11]; // D[a][b]=the decision (value of k) that gets T[a][b]

// Top-down version
int MatChain(int a, int b) {
    if (a == b) return 0; // Only one matrix, no multiplication needed

    if (T[a][b] != -1) return T[a][b]; // If already computed

    int minCost = INT_MAX;
    for (int k = a; k < b; ++k) {
        int cost = MatChain(a, k) + MatChain(k + 1, b) + p[a] * p[k + 1] * p[b + 1];
        if (cost < minCost) {
            minCost = cost;
            D[a][b] = k;
        }
    }

    return T[a][b] = minCost;
}

void MatChainTopDown(int n) {
    memset(T, -1, sizeof(T));
    MatChain(0, n - 1);
}

// Bottom-up version
void MatChainBottomUp(int n) {
    memset(T, 0, sizeof(T));

    for (int len = 2; len <= n; ++len) { // Length of the sub-chain
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            T[i][j] = INT_MAX;

            for (int k = i; k < j; ++k) {
                int cost = T[i][k] + T[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                if (cost < T[i][j]) {
                    T[i][j] = cost;
                    D[i][j] = k;
                }
            }
        }
    }
}

// Recursive to output the solution for both versions
void MatChainSol(int a, int b) {
    if (a == b) {
        cout << "A" << (a + 1);
        return;
    }

    cout << "(";
    MatChainSol(a, D[a][b]);
    cout << " x ";
    MatChainSol(D[a][b] + 1, b);
    cout << ")";
}

void Compute() {
    int caseNum = 1;

    while (true) {
        int n;
        cin >> n;
        if (n == 0) break;

        for (int i = 0; i < n; ++i) {
            cin >> p[i] >> p[i + 1];
        }

        MatChainBottomUp(n);

        cout << "Case " << caseNum++ << ": ";
        MatChainSol(0, n - 1);
        cout << endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    // freopen("input_assign10_00348.txt", "r", stdin);
    Compute();
    return 0;
}