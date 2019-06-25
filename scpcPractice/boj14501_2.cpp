#include <bits/stdc++.h>
using namespace std;
int N, T, P, ans;
int dp[21];
int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d %d", &T, &P);
		for (int j = i + T; j <= N+1; j++) { dp[j] = max(dp[j], dp[i] + P); }
	}
	printf("%d\n", dp[N+1]);
}