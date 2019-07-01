#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
int dp[110][100010];
int N, K, ans;
int w[100010];
int v[100010];

int solution(int pos, int weight) {
	if (weight>K) return -INF;
	if (pos == N) return 0;
	int &ret = dp[pos][weight];
	if (ret != -1) return ret;
	ret = solution(pos + 1, weight);
	ret = max(ret, solution(pos + 1, weight + w[pos]) + v[pos]);
	return ret;
}


int main() {
	memset(dp, -1, sizeof(dp));
	scanf("%d %d", &N, &K);
	for (int i = 0; i<N; i++) {
		scanf("%d %d", &w[i], &v[i]);
	}
	ans = solution(0, 0);
	printf("%d\n", ans);
}