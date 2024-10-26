#include <iostream>
using namespace std;

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        // Cờ để kiểm tra nếu không có hoán đổi nào thì dừng sớm
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Hoán đổi
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        // Nếu không có hoán đổi nào, mảng đã sắp xếp
        if (!swapped) break;
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << "Mảng ban đầu: ";
    printArray(arr, n);
    bubbleSort(arr, n);
    cout << "Mảng sau khi sắp xếp: ";
    printArray(arr, n);
    return 0;
}
