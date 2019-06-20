#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define INF 1e9
int N, A, B;
ll a[200010], ans;
ll sum[200010];

vector<vector<int> > adj;
ll dfs(int here, int pp, int cnt = 0) {
	ans += (cnt * a[here]);
	sum[here] = a[here];
	for (int there : adj[here]) {
		if (there == pp) continue;
		sum[here] += dfs(there,here, cnt + 1);
	}
	return sum[here];
}

void solve(int here, int pp, ll res) {
	ans = max(ans, res);
	for (int there : adj[here]) {
		if (there == pp) continue;
		res -= sum[there];
		res += (sum[1] - sum[there]);
		solve(there, here, res);
		res += sum[there];
		res -= (sum[1] - sum[there]);
	}
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%lld", &a[i]);
	}
	adj.resize(N + 1);
	for (int i = 1; i < N; i++) {
		scanf("%d %d", &A, &B);
		adj[A].push_back(B);	
		adj[B].push_back(A);
	}
	dfs(1,0);
	solve(1, 0, ans);
	printf("%lld\n", ans);
}