#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll dp[100010][2];
ll h[100010][2];
int n;

ll solution(int pos, int ud) {
	if (pos >= n) return 0;
	ll &ret = dp[pos][ud];
	if (ret != -1) return ret;
	ret = 0;
	ret = max(solution(pos + 1, (ud + 1) % 2) + h[pos][ud], max(solution(pos + 1, 0), solution(pos + 1, 1)));
	return ret;
}

int main()
{
	memset(dp, -1, sizeof(dp));
	scanf("%d", &n);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%lld", &h[j][i]);
		}
	}
	ll ans = max(solution(0, 0), solution(0, 1));
	printf("%lld\n", ans);
}