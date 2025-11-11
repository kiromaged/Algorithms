#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// This function merges two halves of the array while counting inversions.
long long CountInvMerge(long long* a, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    long long* leftArr = new long long[n1];
    long long* rightArr = new long long[n2];

    for (int i = 0; i < n1; ++i) leftArr[i] = a[left + i];
    for (int j = 0; j < n2; ++j) rightArr[j] = a[mid + 1 + j];

    int i = 0, j = 0, k = left;
    long long inv_count = 0;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            a[k++] = leftArr[i++];
        } else {
            a[k++] = rightArr[j++];
            inv_count += (n1 - i);  // Count inversions
        }
    }

    while (i < n1) a[k++] = leftArr[i++];
    while (j < n2) a[k++] = rightArr[j++];

    delete[] leftArr;
    delete[] rightArr;

    return inv_count;
}

// This function recursively divides the array and counts inversions using merge sort.
long long CountInv(long long* a, int left, int right) {
    long long inv_count = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;

        inv_count += CountInv(a, left, mid);
        inv_count += CountInv(a, mid + 1, right);
        inv_count += CountInvMerge(a, left, mid, right);
    }
    return inv_count;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    int n;
    while (cin >> n && n != 0) {
        long long* a = new long long[n];
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        long long result = CountInv(a, 0, n - 1);
        cout << result << endl;

        delete[] a;
    }

    return 0;
}
