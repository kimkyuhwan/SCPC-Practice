#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
int N;
struct Edge {
	int v, cap, rev;
	Edge(int _v, int _cap, int _rev) : v(_v), cap(_cap), rev(_rev) {}
};

struct hopCroft {
	int n;
	vector<int> a, b, dist, match, work;
	vector<vector<int>> vt;
	hopCroft(int n) :n(n) {
		a.assign(n + 1, -1);
		b.assign(n + 1, -1);
		dist.assign(n + 1, 0);
		match.assign(n + 1, 0);
		vt.resize(n + 1);
	}
	void addEdge(int x, int y) {
		vt[x].push_back(y);
	}
	void bfs() {
		queue<int> qu;
		for (int i = 1; i <= n; i++) {
			if (!match[i]) {
				dist[i] = 0;
				qu.push(i);
			}
			else
				dist[i] = INF;
		}
		while (qu.size()) {
			int here = qu.front();
			qu.pop();
			for (auto there : vt[here]) {
				if (b[there] != -1 && dist[b[there]] == INF) {
					dist[b[there]] = dist[here] + 1;
					qu.push(b[there]);
				}
			}
		}
	}
	bool dfs(int here) {
		for (int &i = work[here]; i < vt[here].size(); i++) {
			int there = vt[here][i];
			if (b[there] == -1 || dist[b[there]] == dist[here] + 1 && dfs(b[there])) {
				match[here] = true;
				a[here] = there;
				b[there] = here;
				return true;
			}
		}
		return false;
	}
	int solve() {
		int ret = 0;
		while (1) {
			work.assign(n + 1, 0);
			bfs();
			int flow = 0;
			for (int i = 1; i <= n; i++)
				if (!match[i] && dfs(i))flow++;
			if (!flow)break;
			ret += flow;
		}
		return ret;
	}
};

vector< vector<pair<int, int> > > v;

void makeEdges() {
	v.resize(N + 1);
}



bool makehopCroft(int value) {
	hopCroft hf(2 * N+1);
	int a, k;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < 2; j++) {
			a = v[i][j].first;
			k = v[i][j].second;
			if (k <= value) {
				hf.addEdge(i, a);
			}
		}
	}
	return hf.solve() == N;
}


void input() {
	scanf("%d", &N);
	makeEdges();
	for (int i = 1; i <= N; i++) {
		v[i].resize(2);
		for (int j = 0; j < 2; j++) {
			scanf(" %d %d", &v[i][j].first, &v[i][j].second);
		}
	}
}

int main() {
	input();
	int L = 0, R = 1e6+1;
	while (L < R) {
		int mid = (L + R) >> 1;
		if (makehopCroft(mid)) {
			R = mid;
		}
		else {
			L = mid + 1;
		}
	}
	if (L == 1e6 + 1) {
		L = -1;
	}
	printf("%d\n", L);
}