#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define INF 1e9
int dfs(ll here) {
	if (here == 1) return 0;
	int ret = INF;
	bool flag = false;
	if (here % 2 == 0) {
		flag = true;
		ret = min(ret, dfs(here / 2) + 1);
	}
	else if (here % 3 == 0) {
		flag = true;
		ret = min(ret, dfs(2 * here / 3) + 1);
	}
	else if (here % 5 == 0) {
		flag = true;
		ret = min(ret, dfs(4 * here / 5) + 1);
	}
	if (!flag) return -1;
	return ret;
}


int q, n;
ll val, ans;
int cnt[3];
int main() {
	scanf("%d", &q);
	for (int i = 0; i < q; i++) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%lld", &val);
			cnt[val % 3]++;
		}
		int minn = min(cnt[1], cnt[2]);
		ans = cnt[0] + minn;
		cnt[1] -= minn;
		cnt[2] -= minn;
		ans += (cnt[1] + cnt[2]) / 3;
		printf("%d\n", ans);
		ans = 0;
		memset(cnt, 0, sizeof(cnt));
	}
	return 0;
}