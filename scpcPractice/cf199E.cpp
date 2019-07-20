#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200010;
int n, m;
int a, b;
int t, v;
vector<vector<int> > edges;
int depth[MAXN], sz[MAXN], cut[MAXN], p[MAXN];
int par[MAXN][20];
int ans[MAXN];
void dfs(int here, int parent, int dep) {
	par[here][0] = parent;
	depth[here] = dep;
	for (int there : edges[here]) {
		if (there == parent) continue;
		dfs(there, here, dep + 1);
	}
}

int getSize(int here, int parent) {
	sz[here] = 1;
	for (int there : edges[here]) {
		if (there == parent || cut[there]) continue;
		sz[here] += getSize(there, here);
	}
	return sz[here];
}

int findCenter(int here, int parent, int cap) {
	for (int there : edges[here]) {
		if (there == parent || cut[there]) continue;
		if (sz[there] > cap) return findCenter(there, here, cap);
	}
	return here;
}

void decompose(int here, int parent) {
	int sz = getSize(here,0)/2;
	int center = findCenter(here, 0, sz);
	if (parent == 0) p[center] = center;
	else p[center] = parent;
	cut[center] = 1;
	for (int there : edges[center]) {
		if (!cut[there]) decompose(there, center);
	}
}

int getLca(int u, int v) {
	if (depth[u]>depth[v])swap(u, v);
	int diff = depth[v] - depth[u];
	int i = 0;
	while (diff) {
		if (diff&(1 << i)) {
			v = par[v][i];
			diff -= (1 << i);
		}
		i++;
	}
	if (u == v)return u;
	for (int i = 19; i >= 0; i--) {
		if (par[u][i] != par[v][i]) {
			u = par[u][i];
			v = par[v][i];
		}
	}
	return par[u][0];
}
int getDist(int u, int v) {
	return depth[u] + depth[v] - (2 * depth[getLca(u, v)]);
}
void update(int here) {
	int there = here;
	while (true) {
		ans[there] = min(ans[there], getDist(here, there));
		if (p[there] == there) break;
		there = p[there];
	}
}

int query(int here) {
	int there = here;
	int ret = 1e9;
	while (true) {
		ret = min(ret, getDist(here, there) + ans[there]);
		if (there == p[there])break;
		there = p[there];
	}
	return ret;
}

int main() {
	scanf("%d %d", &n, &m);
	edges.resize(n + 1);
	for (int i = 1; i < n; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
		ans[i] = 1e9;
	}
	ans[n] = 1e9;
	dfs(1, 0, 0);
	for (int i = 1; i < 20; i++) {
		for (int j = 1; j <= n; j++) {
			par[j][i] = par[par[j][i - 1]][i - 1];
		}
	}
	decompose(1, 0);
	update(1);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &t, &v);
		if (t == 1) {
			update(v);
		}
		else if(t==2){
			printf("%d\n", query(v));
		}
	}
	return 0;
}