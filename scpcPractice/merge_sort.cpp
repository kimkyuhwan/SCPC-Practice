#include <cstdio>

int N;
int arr[1000010];
int temp[1000010];
void merge(int *data, int start, int end) {
	int mid = (start + end) >> 1;
	
	int aa = start;
	int bb = mid;
	int pt = 0;
	while (aa < mid && bb < end) {
		if (data[aa] < data[bb]) {
			temp[pt++] = data[aa++];
		}
		else {
			temp[pt++] = data[bb++];
		}
	}
	for (int i = aa; i < mid; i++) temp[pt++] = data[i];
	for (int i = bb; i < end; i++) temp[pt++] = data[i];
	for (int i = 0; i < pt; i++) {
		data[i + start] = temp[i];
	}
}


void mergeSort(int *data, int start, int end) {
	if (end - start > 1){
		int mid = (start + end) >> 1;
		mergeSort(data, start, mid);
		mergeSort(data, mid, end);
		merge(data, start, end);
	}
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}
	mergeSort(arr, 0, N);
	for (int i = 0; i < N; i++) {
		printf("%d\n", arr[i]);
	}

}