
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Obj
{
    int v; // value (price) of object
    int w; // weight of object
};

Obj a[1000];

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T1[1001][31];

int Knapsack1(int n, int w) {
    if (n == 0 || w == 0) return 0;
    if (T1[n][w] != -1) return T1[n][w];

    if (a[n - 1].w > w)
        T1[n][w] = Knapsack1(n - 1, w);
    else
        T1[n][w] = max(Knapsack1(n - 1, w), a[n - 1].v + Knapsack1(n - 1, w - a[n - 1].w));

    return T1[n][w];
}

int ComputeKnapsack1(int N, int W) {
    memset(T1, -1, sizeof(T1));
    return Knapsack1(N, W);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T2[1001][31];

int ComputeKnapsack2(int N, int W) {
    memset(T2, 0, sizeof(T2));

    for (int i = 1; i <= N; ++i) {
        for (int w = 0; w <= W; ++w) {
            if (a[i - 1].w > w)
                T2[i][w] = T2[i - 1][w];
            else
                T2[i][w] = max(T2[i - 1][w], a[i - 1].v + T2[i - 1][w - a[i - 1].w]);
        }
    }

    return T2[N][W];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T3[2][31];

int ComputeKnapsack3(int N, int W) {
    memset(T3, 0, sizeof(T3));

    for (int i = 1; i <= N; ++i) {
        for (int w = 0; w <= W; ++w) {
            if (a[i - 1].w > w)
                T3[i % 2][w] = T3[(i - 1) % 2][w];
            else
                T3[i % 2][w] = max(T3[(i - 1) % 2][w], a[i - 1].v + T3[(i - 1) % 2][w - a[i - 1].w]);
        }
    }

    return T3[N % 2][W];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T4[31];

int ComputeKnapsack4(int N, int W) {
    memset(T4, 0, sizeof(T4));

    for (int i = 0; i < N; ++i) {
        for (int w = W; w >= a[i].w; --w) {
            T4[w] = max(T4[w], a[i].v + T4[w - a[i].w]);
        }
    }

    return T4[W];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ComputeKnapsack(int N, int W) {
    //return ComputeKnapsack1(N, W);
    //return ComputeKnapsack2(N, W);
    //return ComputeKnapsack3(N, W);
    return ComputeKnapsack4(N, W);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;
        for (int i = 0; i < N; ++i)
            cin >> a[i].v >> a[i].w;

        int G, totalValue = 0;
        cin >> G;

        while (G--) {
            int MW;
            cin >> MW;
            totalValue += ComputeKnapsack(N, MW);
        }

        cout << totalValue << endl;
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
