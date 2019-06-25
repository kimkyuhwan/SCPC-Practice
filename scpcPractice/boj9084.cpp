#include <bits/stdc++.h>
using namespace std;
int T, N, M, C;
int dp[10010];
int money[22];
int main() {
	scanf("%d", &T);
	for (int t = 0; t < T; t++) {
		memset(dp, 0, sizeof(dp));
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%d", &money[i]);
		}
		scanf("%d", &M);
		for (int i = 0; i < N; i++) {
			C = money[i];
			dp[C]++;
			for (int j = C; j <= M; j++) {
				dp[j] += dp[j - C];
			}
		}
		printf("%d\n", dp[M]);
	}
}