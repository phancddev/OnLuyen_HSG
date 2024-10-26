#include <bits/stdc++.h>
using namespace std;
#define el "\n";


void bubbleSort(int arr[], int n, int lengthOfARR) { 
    
for(int i = 0; i < lengthOfARR - 1; i++) {
    bool swapped = false;
    for(int j = 0; j < lengthOfARR - i - 1; j++)
    if(arr[j] > arr[j+1] ) {
       swap(arr[j], arr[j+1]);
       swapped = true;
    }
if(!swapped) break;
}
}
int main() {
    freopen("bubbleSort.inp", "r", stdin);
    freopen("bubbleSort.out", "w", stdout);
    int lengthOfARR; cin >> lengthOfARR;
    int arr[lengthOfARR];
    int n = lengthOfARR;
    for(int i = 0; i < lengthOfARR; i++) {
        // cout << "Nhap so thu" <<" " << i << el;
        cin >> arr[i]; 

    }
    bubbleSort(arr, n,lengthOfARR);
    cerr << "Mang sau khi duoc sap xep la: " << el;
    for(int i = 0; i < lengthOfARR; i++) {
        cout << arr[i] << " " << el;
        // cerr << arr[i] << " " << el;
    }
    
    return 0;
}