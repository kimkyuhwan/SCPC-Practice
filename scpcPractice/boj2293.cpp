#include <bits/stdc++.h>
using namespace std;
int dp[10010];
int arr[110];
int n, k;
int main() {
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	dp[0] = 1;
	for (int i = 0; i < n; i++) {
		for (int j = arr[i]; j <= k; j++) {
			dp[j] += dp[j - arr[i]];
		}
	}
	printf("%d\n", dp[k]);
}