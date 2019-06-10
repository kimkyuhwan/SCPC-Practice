#include <bits/stdc++.h>
using namespace std;
int N, val, ans;
int dp[1010], A[1010];
int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &A[i]);
		dp[i] = A[i];
		for (int j = 0; j < i; j++) {
			if (A[j] < A[i]) {
				dp[i] = max(dp[j] + A[i], dp[i]);
			}
		}
		ans = max(ans, dp[i]);
	}
	printf("%d\n", ans);
	return 0;
}