#include <bits/stdc++.h>
using namespace std;
int N, M, sum, maxx;
int arr[100010];
vector<int> vec;
int main() {
	int a = vec.size() - 1;
	scanf("%d %d", &N, &M);
	for (int i = 0; i<N; i++) {
		scanf("%d", &arr[i]);
	}
	sort(arr, arr + N);
	for (int i = 0; i<N; i++) {
		for (int j = i + 1; j<N; j++) {
			int remainValue = M - arr[i] - arr[j];
			int idx = upper_bound(arr+j, arr + N, remainValue) - arr;
			if (idx > N || idx==0) continue;
			else idx--;
			sum = arr[i] + arr[j] + arr[idx];
			if (sum > M) continue;
			maxx = max(maxx, sum);
		}
	}
	printf("%d\n", maxx);
}