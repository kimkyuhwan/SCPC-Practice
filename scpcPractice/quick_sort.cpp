#include <cstdio>
int data[1000010], N;
void swap(int &i, int &j) {
	int temp = i;
	i = j;
	j = temp;
}

void quickSort(int* data, int begin, int end) {
	if (begin >= end) return;
	int pivot = begin;
	int f = pivot + 1;
	int b = end;
	while (f <= b) {
		while (f <= end && data[f] <= data[pivot]) f++;
		while (b > begin && data[b] > data[pivot]) b--;
		if (f > b) swap(data[b], data[pivot]);
		else swap(data[f], data[b]);
	}
	quickSort(data, begin, b - 1);
	quickSort(data, b + 1, end);
}
int main()
{
	scanf("%d", &N);
	for (int i = 0; i<N; i++) {
		scanf("%d", &data[i]);
	}
	quickSort(data, 0, N - 1);
	for (int i = 0; i<N; i++) {
		printf("%d\n", data[i]);
	}
	return 0;
}