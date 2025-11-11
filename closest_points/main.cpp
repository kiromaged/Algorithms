#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Point
{
    double x, y;
};

bool IsBeforeX(Point& a, Point& b) { return a.x < b.x; }
bool IsBeforeY(Point& a, Point& b) { return a.y < b.y; }

double dist(Point& a, Point& b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    if (n <= 1) return;

    int mid = n / 2;
    Type* left = new Type[mid];
    Type* right = new Type[n - mid];

    for (int i = 0; i < mid; i++) left[i] = a[i];
    for (int i = mid; i < n; i++) right[i - mid] = a[i];

    Merge(left, mid, IsBefore);
    Merge(right, n - mid, IsBefore);

    int i = 0, j = 0, k = 0;
    while (i < mid && j < n - mid) {
        if (IsBefore(left[i], right[j])) a[k++] = left[i++];
        else a[k++] = right[j++];
    }

    while (i < mid) a[k++] = left[i++];
    while (j < n - mid) a[k++] = right[j++];

    delete[] left;
    delete[] right;
}

template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    Merge(a, n, IsBefore);
}


double ClosestPair(Point* p, int n)
{
    if (n <= 1) return 1e9;

    // Sort points by x-coordinate
    MergeSort(p, n, IsBeforeX);

    // Helper function for closest pair recursive divide and conquer
    double closest = 1e9;

    Point* temp = new Point[n];

    // Recursive function to find the closest pair
    function<double(int, int)> closestPairRecursive = [&](int left, int right) -> double {
        if (right - left <= 3) {
            double minDist = 1e9;
            for (int i = left; i < right; i++) {
                for (int j = i + 1; j < right; j++) {
                    minDist = min(minDist, dist(p[i], p[j]));
                }
            }
            return minDist;
        }

        int mid = (left + right) / 2;
        double leftClosest = closestPairRecursive(left, mid);
        double rightClosest = closestPairRecursive(mid, right);
        closest = min(leftClosest, rightClosest);

        // Merge the points on the dividing line
        int tempCount = 0;
        for (int i = left; i < right; i++) {
            if (fabs(p[i].x - p[mid].x) < closest) {
                temp[tempCount++] = p[i];
            }
        }


        for (int i = 0; i < tempCount; i++) {
            for (int j = i + 1; j < tempCount && temp[j].y - temp[i].y < closest; j++) {
                closest = min(closest, dist(temp[i], temp[j]));
            }
        }

        return closest;
    };

    closest = closestPairRecursive(0, n);
    delete[] temp;

    return closest;
}

int main()
{
    while (true) {
        int N;
        cin >> N;
        if (N == 0) break;

        Point* points = new Point[N];
        for (int i = 0; i < N; i++) {
            cin >> points[i].x >> points[i].y;
        }

        double result = ClosestPair(points, N);

        if (result >= 10000) {
            cout << "INFINITY" << endl;
        } else {
            printf("%.4f\n", result);
        }

        delete[] points;
    }
    return 0;
}
