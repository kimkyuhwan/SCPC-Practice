#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pint;
const int MAXN = 100007;
int N, M;
int a, b, c;
vector<vector<pint> > edges;
int depth[MAXN], numberOfChild[MAXN], parent[MAXN], spa[MAXN][20], ex[MAXN], ey[MAXN];
vector<pint> grp[MAXN];
pint id[MAXN];
void add(int x, int y, int wt) {
	b[np] = y; w[np] = wt; nxt[np] = st[x]; st[x] = np++;
}

struct tree {
	int root[MAXN], sz[MAXN], t[MAXN * 2], left[MAXN * 2], right[MAXN * 2], now;
	int construct(int groupNumber, int start, int end) {
		int x = now++;
		if (start == end) t[x] = grp[groupNumber][start].second;
		else {
			int mid = (start + end) >> 1;
			left[x] = construct(groupNumber, start, mid);
			right[x] = construct(groupNumber, mid+1, end);
			t[x] = max(t[left[x]], t[right[x]]);
		}
		return x;
	}
	void construct(int groupNumber, int k) {
		root[k] = construct(groupNumber, 0, grp[groupNumber].size() - 1); sz[k] = grp[groupNumber].size();
	}
	void update(int start, int end, int x, int p, int v) {
		if (start == end) t[x] = v;
		else {
			int mid = (start + end) >> 1;
			if (p <= mid) update(start, mid, left[x], p, v);
			else update(mid + 1, end, right[x], p, v);
			t[x] = max(t[left[x]], t[right[x]]);
		}
	}
	void update(int k, int p, int v) {
		update(0, sz[k] - 1, root[k], p, v);
	}
	int query(int start, int end, int x, int ql, int qr) {
		if (ql <= start && end <= qr) return t[x];
		else if (ql <= end && start <= qr) {
			int mid = (start + end) >> 1;
			return max(query(start, mid, left[x], ql, qr), query(mid + 1, end, right[x], ql, qr));
		}
		return 0;
	}
	int query(int k, int left, int right) {
		return query(0, sz[k] - 1, root[k], left, right);
	}
}t;


int getChildNumber(int here, int par,int dep) {
	numberOfChild[here] = 1;
	depth[here] = dep;
	parent[here] = par;
	for (int i = 0; i < edges[here].size(); i++) {
		int there = edges[here][i].first;
		if (there == par) continue;
		numberOfChild[here] += getChildNumber(there, here,dep+1);
	}
	return numberOfChild[here];
}

void dfs(int here, int weight, int grpNumber) {
	grp[grpNumber].emplace_back(here,weight);
	int heavy = 0, maxx = 0;
	for (int i = 0; i < edges[here].size(); i++) {
		int there = edges[here][i].first;
		int w = edges[here][i].second;
		if (there == parent[here]) continue;
		if (maxx < numberOfChild[there]) heavy = there, maxx = numberOfChild[there];
	}
	for (int i = 0; i < edges[here].size(); i++) {
		int there = edges[here][i].first;
		int w = edges[here][i].second;
		if (there == heavy) dfs(there, w, grpNumber);
		else dfs(there, w, grpNumber + 1);
	}
}

int lca(int x, int y) {
	if (depth[x] > depth[y]) return lca(y, x);
	for (int i = 19, d = depth[y] - depth[x]; ~i; i--) if ((d >> i) & 1) y = spa[y][i];
	for (int i = 19; ~i; i--) if (spa[x][i] != spa[y][i]) x = spa[x][i], y = spa[y][i];
	return x == y ? x : spa[x][0];
}

int down(int x, int p) {
	if (id[x].first == id[p].first) return t.query(id[x].first, id[p].second + 1, id[x].second);
	return max(t.query(id[x].first, 0, id[x].second), down(parent[grp[id[x].first][0].first], p));
}

int query(int x, int y) {
	int l = lca(x, y);
	return max(down(x, l), down(y, l));
}

int main()
{
	scanf("%d", &N);
	edges.resize(N + 1);
	for (int i = 1; i < N; i++) {
		scanf("%d %d %d", &a, &b, &c);
		edges[a].push_back({ b,c });
		edges[b].push_back({ a,c });
	}
	getChildNumber(1, 1, 1);
	dfs(1, 0, 0);

	for (int i = 0; i<MAXN; i++)
		for (int j = 0; j<grp[i].size(); j++) id[grp[i][j].first] = pint(i, j);

	scanf("%d", &M);

	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &a, &b, &c);
		if (a == 1) {
			b = depth[]
		}
		else if(a==2){

		}
	}
}