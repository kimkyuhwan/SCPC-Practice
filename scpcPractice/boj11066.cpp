#include <bits/stdc++.h>
using namespace std;
#define LINF 1e18
typedef long long ll;
ll dp[510][510];
int N, T;
ll arr[510];
ll psum[510];

int main() {
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		memset(dp, 0, sizeof(dp));
		scanf("%d", &N);
		for (int j = 1; j <= N; j++) {
			scanf("%lld", &arr[j]);
			psum[j] = psum[j - 1] + arr[j];
		}
		for (int len = 1;len< N; len++) {
			for (int l = 1; l + len <= N; l++) {
				int r = l + len;
				ll &ret = dp[l][r];
				ret = LINF;
				for (int k = l; k < r; k++) {
					ret = min(ret, dp[l][k] + dp[k + 1][r] + psum[r] - psum[l - 1]);
				}
			}
		}
		printf("%lld\n", dp[1][N]);
	}
}