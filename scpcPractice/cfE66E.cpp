#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m, a, b;

int dp[500010][21];

int solution(int src, int dst) {
	int ret = 0;
	if (dp[src][0] == -1) {
		return -2;
	}
	for (int i = 20; i >= 0; i--) {
		if (dp[src][i] == -1) continue;
		if (dp[src][i] < dst) {
			ret += (1 << i);
			src = dp[src][i];
		}
	}
	return ret;
}

int main() {
	memset(dp, -1, sizeof(dp));
	scanf("%d %d", &n, &m);		
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &a, &b);
		dp[a][0] = max(dp[a][0], b);
	}
	for (int i = 0; i < 500000; i++) {
		dp[i + 1][0] = max(dp[i + 1][0], dp[i][0]);
	}
	for (int i = 1; i <= 20; i++) {
		for (int j = 0; j <= 500000; j++) {
			if (dp[j][i - 1] != -1) {
				dp[j][i] = dp[dp[j][i - 1]][i - 1];
			}
		}
	}
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		int ans = solution(a, b) + 1;
		if (n < ans) {
			ans = -1;
		}
		printf("%d\n", ans);
	}
}