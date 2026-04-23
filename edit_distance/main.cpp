#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

char a[82]; // First string
char b[82]; // Second string

int D[81][81]; // D[][] is the same for all versions (no memory reduction)

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Recursive version with memoization
int T1[81][81];
int EditDist1(int n, int m) {
    if (n == 0) return m; // If the first string is empty, insert all characters of the second string
    if (m == 0) return n; // If the second string is empty, remove all characters of the first string

    if (T1[n][m] != -1) return T1[n][m]; // If already computed, return the result

    if (a[n-1] == b[m-1]) {
        return T1[n][m] = EditDist1(n-1, m-1); // No operation needed if characters are equal
    } else {
        // Try all three operations: insert, delete, and replace
        int insert = EditDist1(n, m-1); // Insert
        int remove = EditDist1(n-1, m); // Remove
        int replace = EditDist1(n-1, m-1); // Replace

        // Find the minimum cost
        return T1[n][m] = 1 + min(min(insert, remove), replace);
    }
}

int ComputeEditDist1(int N, int M) {
    memset(T1, -1, sizeof(T1)); // Initialize memoization table
    return EditDist1(N, M);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Bottom-up version (without space optimization)
int T2[81][81];
int ComputeEditDist2(int N, int M) {
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= M; j++) {
            if (i == 0) {
                T2[i][j] = j; // If the first string is empty, insert all characters of the second string
            } else if (j == 0) {
                T2[i][j] = i; // If the second string is empty, remove all characters of the first string
            } else {
                int insert = T2[i][j-1]; // Insert
                int remove = T2[i-1][j]; // Remove
                int replace = T2[i-1][j-1]; // Replace

                // If characters are equal, no operation needed
                if (a[i-1] != b[j-1]) {
                    T2[i][j] = 1 + min(min(insert, remove), replace);
                } else {
                    T2[i][j] = T2[i-1][j-1]; // No operation needed if characters are equal
                }
            }
        }
    }
    return T2[N][M];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Bottom-up version using only two rows (space optimized)
int T3[2][81];
int ComputeEditDist3(int N, int M) {
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= M; j++) {
            if (i == 0) {
                T3[i%2][j] = j; // If the first string is empty, insert all characters of the second string
            } else if (j == 0) {
                T3[i%2][j] = i; // If the second string is empty, remove all characters of the first string
            } else {
                int insert = T3[(i-1)%2][j-1]; // Insert
                int remove = T3[i%2][j]; // Remove
                int replace = T3[(i-1)%2][j-1]; // Replace

                // If characters are equal, no operation needed
                if (a[i-1] != b[j-1]) {
                    T3[i%2][j] = 1 + min(min(insert, remove), replace);
                } else {
                    T3[i%2][j] = T3[(i-1)%2][j-1]; // No operation needed if characters are equal
                }
            }
        }
    }
    return T3[N%2][M];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Bottom-up version using maximum space optimization (only one row used)
int T4[81];
int ComputeEditDist4(int N, int M) {
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= M; j++) {
            if (i == 0) {
                T4[j] = j; // If the first string is empty, insert all characters of the second string
            } else if (j == 0) {
                T4[j] = i; // If the second string is empty, remove all characters of the first string
            } else {
                int insert = T4[j-1]; // Insert
                int remove = T4[j]; // Remove
                int replace = T4[j-1]; // Replace

                // If characters are equal, no operation needed
                if (a[i-1] != b[j-1]) {
                    T4[j] = 1 + min(min(insert, remove), replace);
                } else {
                    T4[j] = T4[j-1]; // No operation needed if characters are equal
                }
            }
        }
    }
    return T4[M];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Oper {
    int n, m;
    int oper;
};

Oper opers[81];

int EditDistSol(int N, int M) {
    int i = N, j = M;
    int count = 0;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && a[i-1] == b[j-1]) {
            i--;
            j--;
        } else {
            if (i > 0 && j > 0 && T2[i][j] == T2[i-1][j-1] + 1) {
                opers[count++] = {i, j, 3}; // Replace
                i--;
                j--;
            } else if (i > 0 && T2[i][j] == T2[i-1][j] + 1) {
                opers[count++] = {i, 0, 2}; // Delete
                i--;
            } else {
                opers[count++] = {j, 0, 1}; // Insert
                j--;
            }
        }
    }
    reverse(opers, opers + count);
    cout << count << endl;
    for (int i = 0; i < count; i++) {
        if (opers[i].oper == 1)
            cout << opers[i].oper << " Insert " << opers[i].n << "," << b[opers[i].n-1] << endl;
        else if (opers[i].oper == 2)
            cout << opers[i].oper << " Delete " << opers[i].n << endl;
        else if (opers[i].oper == 3)
            cout << opers[i].oper << " Replace " << opers[i].n << "," << b[opers[i].n-1] << endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ComputeEditDist(int N, int M) {
    return ComputeEditDist4(N, M); // Use the 4th version by default
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Compute() {
    int cas = 0;
    while (true) {
        a[0] = 0; b[0] = 0;
        if (!fgets(a, 82, stdin)) break;
        fgets(b, 82, stdin);
        a[strlen(a)-1] = 0;
        b[strlen(b)-1] = 0;
        if (cas) cout << endl;
        int N = strlen(a), M = strlen(b);
        ComputeEditDist(N, M);
        EditDistSol(N, M);
        cas++;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    //freopen("input_assign11_00526.txt", "r", stdin);
    Compute();
    return 0;
}
