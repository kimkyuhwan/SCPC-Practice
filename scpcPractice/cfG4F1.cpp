#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll dp[510][510];
int n, m;
int pos[510];
int val;

ll solution(int idx, int p) {
	if (idx == n) return 1;
	ll &ret = dp[idx][p];
	if (ret != -1) return ret;
	ret = 0;
	int ff = pos[idx];

}

int main()
{
	memset(dp, -1, sizeof(dp));
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &val);
		pos[val] = i;
	}
	printf("%lld\n", solution(0, 0));
}