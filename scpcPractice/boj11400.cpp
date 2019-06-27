#include <bits/stdc++.h>
using namespace std;
int V, E, K, A, B, cnt;
vector<vector<int> > adj;
vector<int> discover;
vector<pair<int, int> > ans;
int dfs(int here, int pp) {
	discover[here] = ++cnt;
	int ret = discover[here];
	for (int there : adj[here]) {
		if (there==pp) continue;
		if (!discover[there]) {
			int thereDiscover = dfs(there, here);
			if (thereDiscover > discover[here]) {
				ans.push_back({ min(here,there),max(here,there) });
			}
			ret = min(ret, thereDiscover);
		}
		else {
			ret = min(ret, discover[there]);
		}
	}
	return ret;
}

int main() {
	scanf("%d %d", &V, &E);
	adj.resize(V + 1);
	discover.resize(V + 1);
	for (int i = 0; i < E; i++) {
		scanf("%d %d", &A, &B);
		adj[A].push_back(B);
		adj[B].push_back(A);
	}
	for (int i = 1; i <= V; i++) {
		if (!discover[i]) {
			dfs(i, 0);
		}
	}
	sort(ans.begin(), ans.end());
	printf("%d\n", ans.size());
	for (int i = 0; i < ans.size(); i++) {
		printf("%d %d\n", ans[i].first, ans[i].second);
	}
}