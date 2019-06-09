#include <bits/stdc++.h>
using namespace std;
#define INF 1e18
typedef long long ll;
struct Edge {
	int v, rev;
	ll cap;
	Edge(int _v, ll _cap, int _rev) : v(_v), cap(_cap), rev(_rev) {}
};

vector<vector<Edge> > edges;
vector<int> isFinish;
vector<int> level, work;
vector<int> ans;
vector< pair<int, int> > used;
map<int, vector<int> > xx, yy;
map<pair<int, int>, int> querys;
int n, m, x, y;
int r, b;
int t, l;
int d[100010];
int vertexCnt[100010];
int startVertex, endVertex, numberOfVertex, newStart, newEnd;
int finishCnt;
bool isNotPossible;

bool canFinish(pair<int, int> src, int idx) {
	return (abs(src.first - src.second) <= d[idx]);
}

void checkFinish(pair<int, int> src, int idx) {
	if (canFinish(src, idx)) {
		isFinish[idx] = true;
		finishCnt++;
	}
}



bool makeLevelGraph() {
	queue<int> q;
	fill(level.begin(), level.end(), -1);
	level[startVertex] = 0;
	q.push(startVertex);
	while (!q.empty()) {
		int here = q.front(); q.pop();
		for (int i = 0; i < edges[here].size(); i++) {
			int there = edges[here][i].v;
			ll thereCap = edges[here][i].cap;
			if (there > n && there <= n + m && isFinish[there - n]) {
				continue;
			}
			if (thereCap > 0 && level[there]==-1) {
				level[there] = level[here] + 1;
				q.push(there);
			}
		}
	}
	return level[endVertex] != -1;
}

ll dfs(int here, ll currentCap) {
	if (here == endVertex) return currentCap;
	for (int &i = work[here]; i < edges[here].size(); i++) {
		int there = edges[here][i].v;
		ll thereCap = edges[here][i].cap;
		if (thereCap > 0) {
			ll cap = dfs(there, min(currentCap, thereCap));
			if (cap > 0) {
				edges[here][i].cap -= cap;
				edges[there][edges[here][i].rev].cap += cap;
				return cap;
			}
		}
	}
	return 0;
}

void executeDinic() {
	ll totalFlow = 0, cost = 0;
	int def = (r < b) ? 0 : 1;
	used.resize(querys.size() + 1);
	ans.resize(n, def);
	while (makeLevelGraph()) {
		fill(work.begin(), work.end(), 0);
		while (1) {
			ll flow = dfs(startVertex, INF);
			if (!flow) break;
			totalFlow += flow;
		}
	}
	if (finishCnt != querys.size()) {
		isNotPossible = true;
	}
}

void addEdge(int start, int end, ll cap) {
	edges[start].emplace_back(end, cap, edges[end].size());
	edges[end].emplace_back(start, 0, edges[start].size() - 1);
}

void makeEdges() {
	edges.resize(numberOfVertex);
	level.resize(numberOfVertex);
	work.resize(numberOfVertex);
	isFinish.resize(m + 1);
}

void input() {
	scanf("%d %d", &n, &m);
	scanf("%d %d", &r, &b);
	startVertex = 0;
	endVertex = n + m + 1;
	newStart = endVertex + 1;
	newEnd = newStart + 1;
	numberOfVertex = newEnd + 1;
	makeEdges();
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &x, &y);
		xx[x].push_back(i);
		yy[y].push_back(i);
		addEdge(startVertex, i, INF);
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", &t, &l, &d[i]);
		if (querys.count({ t,l })) {
			querys[{t, l}] = min(querys[{t, l}], d[i]);
		}
		else {
			querys[{t, l}] = d[i];
		}
	}
	int i = 1;
	for (auto it = querys.begin(); it != querys.end(); it++, i++) {
		t = it->first.first;
		l = it->first.second;
		int dd = it->second;
		d[i] = dd;
		if (t == 1) {
			for (int j = 0; j < xx[l].size(); j++) {
				int here = xx[l][j];
				int minn = min(r, b);
				int maxx = max(r, b);
				addEdge(here, n + i, minn, -1);
				addEdge(here, n + i, maxx - minn, 1);
			}
			vertexCnt[i] = xx[l].size();

		}
		else {
			for (int j = 0; j < yy[l].size(); j++) {
				int here = yy[l][j];
				int minn = min(r, b);
				int maxx = max(r, b);
				addEdge(here, newEnd, minn);
				addEdge(newStart, n + i, maxx - minn);
			}
			vertexCnt[i] = xx[l].size();
		}
		addEdge(n + i, endVertex, INF, 0);
	}
}
int main() {
	input();
	executeDinic();
	if (isNotPossible) {
		puts("-1");
	}
	else {
		ll sol = 0;
		for (int i = 0; i < ans.size(); i++) {
			sol += ans[i] == 0 ? r : b;
		}
		printf("%lld\n", sol);
		for (int i = 0; i < ans.size(); i++) {
			printf("%c", ans[i] == 0 ? 'r' : 'b');
		}
	}
}