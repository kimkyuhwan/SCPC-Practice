#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 100007;
int N, Q;
int u, v;
ll L, h[MAXN];
int cut[MAXN], numberOfChild[MAXN];
int ans[MAXN];
vector<vector<pair<int, ll> > > edges;
vector< vector<pair<ll, int> > > query;
vector<ll> tot, hereD;
vector<int> nodes;

int dfs(int here, bool totalSave = 0, int parent = -1, ll hereDist =0) {
	h[here] = hereDist;
	numberOfChild[here] = 1;
	hereD.push_back(hereDist);
	nodes.push_back(here);
	if (totalSave) {
		tot.push_back(hereDist);
	}
	for (int i = 0; i < edges[here].size(); i++) {
		int there = edges[here][i].first;
		ll thereDist = edges[here][i].second + hereDist;
		if (there == parent || cut[there]) continue;
		numberOfChild[here] += dfs(there, totalSave, here, thereDist);
	}
	return numberOfChild[here];
}

int findCenter(int here, int parent, int cap) {
	for (int i = 0; i < edges[here].size(); i++) {
		int there = edges[here][i].first;
		if (there == parent || cut[there]) continue;
		if (numberOfChild[there] > cap) return findCenter(there, here, cap);
	}
	return here;
}


void solve(int here) {
	int sz = dfs(here);
	int center = findCenter(here, -1,sz/2);
	tot.clear();
	dfs(center, 1);
	cut[center] = 1;
	sort(tot.begin(), tot.end());
	for (int i = 0; i < query[center].size(); i++) {
		ll dist = query[center][i].first;
		int idx = query[center][i].second;
		ans[idx] += (upper_bound(tot.begin(), tot.end(), dist) - tot.begin() -1);
	}
	for (int i = 0; i < edges[center].size(); i++) {
		int there = edges[center][i].first;
		ll thereDist = edges[center][i].second;
		if (cut[there]) continue;
		nodes.clear();
		hereD.clear();
		dfs(there, 0, center, thereDist);
		sort(hereD.begin(), hereD.end());
		for (int u : nodes) {
			for (int k = 0; k < query[u].size(); k++) {
				ll ww = query[u][k].first;
				int idx = query[u][k].second;
				ans[idx] += upper_bound(tot.begin(), tot.end(), ww - h[u]) - tot.begin();
				ans[idx] -= upper_bound(hereD.begin(), hereD.end(), ww - h[u]) - hereD.begin();
			}
		}
	}
	for (int i = 0; i < edges[center].size(); i++) {
		int there = edges[center][i].first;
		if (!cut[there]) solve(there);
	}
}



int main() {
	scanf("%d %d", &N, &Q);
	edges.resize(N + 1);
	for (int i = 1; i < N; i++) {
		scanf("%d %d %dll", &u, &v, &L);
		edges[u].push_back({ v,L });
		edges[v].push_back({ u,L });
	}
	query.resize(N+1);
	for (int i = 0; i < Q; i++) {
		scanf("%d %lld", &u, &L);
		query[u].push_back({ L,i });
	}
	solve(1);
	for (int i = 0; i < Q; i++) {
		printf("%d\n", ans[i]+1);
	}
}