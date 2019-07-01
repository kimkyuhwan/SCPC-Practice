#include <bits/stdc++.h>
using namespace std;
int N, M;
int a, b;
int arr[4010];
int p[4010];

void manacher() {
	int r = -1, c = -1;
	for (int i = 0; i < N; i++) {
		if (r >= i) p[i] = min(r - i, p[c * 2 - i]); 
		else p[i] = 0;

		while (i + p [i] + 1 < N && i - p[i] - 1 >= 0 && arr[i + p[i] + 1] == arr[i - p[i] - 1]) p[i]++; 
		if (i + p[i] > r) {
			r = i + p[i];
			c = i;
		}
	}
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}
	for (int i = N-1; i >=0; i--) {
		arr[(i << 1) + 1] = arr[i];
		arr[i << 1] = -1;
	}
	N <<= 1;
	arr[N++] = -1;
	manacher();
	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &a, &b);
		int cnt = (b - a) + 1;
		a = (a << 1) - 1;
		b = (b << 1) - 1;
		int mid = (a + b) >> 1;
		if (p[mid] >= cnt) {
			puts("1");
		}
		else {
			puts("0");
		}
	}
}