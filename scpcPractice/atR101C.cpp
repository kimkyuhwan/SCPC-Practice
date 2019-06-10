#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
int N, K;
int arr[100010];
int L, R;
void input() {
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
		if (arr[i] < 0) {
			L++;
		}
		else if (arr[i] == 0) {
			K--;
			N--;
			i--;
		}
	}
}
int main() {
	input();
	int sol = INF;
	if (K == 0) {
		puts("0");
		return 0;
	}
	for (int i = 0; i < N; i++) {
		int val = INF;
		if (i < L) {
			int left = i, right = (i + K-1);
			if (right < N) {
				val = abs(arr[i]);
				if (right >= L) {
					val+=abs(arr[right] - arr[left]);
				}
			}
		}
		else {
			int left = (i-K+1), right = i;
			if (left >= 0) {
				val = abs(arr[i]);
				if (left < L) {
					val += abs(arr[right] - arr[left]);
				}
			}
		}
		sol = min(sol, val);
	}
	printf("%d\n", sol);
}