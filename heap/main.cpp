#include <bits/stdc++.h>
using namespace std;
void max_heapfy(vector<int>&arr,int i,int n){
    int largest=i;
    int right =2*i+2;
    int left=2*i+1;
    if(i!=largest){
        swap(arr[largest],arr[i]);
        max_heapfy(arr,largest,n);
    }
}
void max_heap(vector<int>&arr){
    int n=arr.size();
    for(int i=n/2-1;i>0;i--){
        max_heapfy(arr,i,n);
    }
}
void heap_sort(vector<int>&arr){
    int n=arr.size();
    max_heap(arr);
    for(int i=n-1;i>0;i--){
        swap(arr[0],arr[i]);
        max_heapfy(arr,0,i);

    }
}
int main() {


}
