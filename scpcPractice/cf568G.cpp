#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MOD 1000000007
int n, t;
ll dp[1 << 15][15];
pair<int, int> val[20];
ll ans;

ll solution(int state, int pos, int sum) {
	if (sum == t) return 1;
	ll &ret = dp[state][pos];
	if (ret != -1) return ret;
	ret = 0;
	for (int i = 0; i < n; i++) {
		if (state & (1 << i)) continue;
		if (val[i].second == val[pos].second) continue;
		int cost = val[i].first;
		if (sum + cost <= t) {
			ret += solution(state | (1 << i), i, sum + cost);
			ret %= MOD;
		}
	}
	return ret%=MOD;
}
int main() {
	memset(dp, -1, sizeof(dp));
	scanf("%d %d", &n, &t);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &val[i].first,&val[i].second);
	}
	for (int i = 0; i < n; i++) {
		ans += solution((1<<i), i ,val[i].first);
		ans %= MOD;
	}
	printf("%lld\n", ans);
}