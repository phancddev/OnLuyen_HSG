#include <bits/stdc++.h>
using namespace std;


void insertionSort(int arr[], int n ) {
for(int i  = 0; i < n; i++) {
    int tmp = arr [i];
    int j = i;
    while (j > 0 && arr[j] > tmp) {
        if(arr[j] > arr[j + 1]) {
            arr[j] = arr[j - 1];
            j = j - 1;
            }
    arr[j] = tmp;
        }
    }
    
}
void printSorted(int arr[], int n) {
    insertionSort(arr, n);
    for(int i = 0; i < n;i++){
        cout << arr[i] <<" ";
    }
    
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    int n;
    cin >> n;
    int arr[n];
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

printSorted(arr, n);

    return 0;
}