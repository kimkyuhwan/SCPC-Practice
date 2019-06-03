#include <bits/stdc++.h>
using namespace std;
int N;
int arr[100010];
vector<int> odd, even;
int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
		if (arr[i] % 2 == 0) even.push_back(arr[i]);
		else odd.push_back(arr[i]);
	}
	if (odd.empty() || even.empty()) {
		for (int i = 0; i < N; i++) {
			printf("%d ", arr[i]);
		}
	}
	else {
		sort(arr, arr + N);
		for (int i = 0; i < N; i++) {
			printf("%d ", arr[i]);
		}
	}
	return 0;
}