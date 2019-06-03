#include <bits/stdc++.h>
using namespace std;
int N;
int arr[2010];
int main() {
	scanf("%d", &N);
	for (int i = 0; i < N*2; i++) 
		scanf("%d", &arr[i]);
	sort(arr, arr + N+N);
	int a = 0, b = 0;
	for (int i = 0; i < N; i++) {
		a += arr[i];
		b += arr[i + N];
	}
	if (a == b) {
		puts("-1");
		return 0;
	}
	else {
		for (int i = 0; i < N + N; i++) {
			printf("%d ", arr[i]);
		}
	}
	return 0;
}