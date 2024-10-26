// hàm sắp xếp nổi bọt (bubble sort)
void BubbleSort(int a[], int n){
    int temp; // biến tạm temp
    for (int i = 0; i < n; i++){
	for (int j = i + 1; j < n; j++){
		if (a[j] > a[j+1]){
                    temp = a[j];
                    a[j] = a[j+1];
                    a[j+1] = temp;
			}
		}
	}
}
