#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
struct Edge {
	int v, cap, rev;
	Edge(int _v, int _cap, int _rev) : v(_v), cap(_cap), rev(_rev) {}
};
int ans;

int K, N, M, a, b, c;
vector<vector<Edge> > edges;
vector<int> work, level;
int startVertex, endVertex, numberOfVertex;
void makeEdges() {
	edges.assign(numberOfVertex + 1, vector<Edge>());
	work.assign(numberOfVertex + 1, 0);
	level.assign(numberOfVertex + 1, -1);
}

void addEdge(int start, int end, int cap) {
	edges[start].emplace_back(end, cap, edges[end].size());
	edges[end].emplace_back(start, 0, edges[start].size() - 1);
}

bool makeLevelGraph() {
	queue<int> q;
	fill(level.begin(), level.end(), -1);
	level[startVertex] = 0;
	q.push(startVertex);
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		for (Edge edge : edges[here]) {
			int there = edge.v;
			int thereCap = edge.cap;
			if (thereCap > 0 && level[there] == -1) {
				level[there] = level[here] + 1;
				q.push(there);
			}
		}
	}
	return level[endVertex] != -1;
}

int dfs(int here, int currentCap) {
	if (here == endVertex) return currentCap;
	for (int &i = work[here]; i < edges[here].size(); i++) {
		int there = edges[here][i].v;
		int thereCap = edges[here][i].cap;
		if (thereCap > 0 && level[there] == level[here] + 1) {
			int cap = dfs(there, min(currentCap, thereCap));
			if (cap > 0) {
				edges[here][i].cap -= cap;
				edges[there][edges[here][i].rev].cap += cap;
				return cap;
			}
		}
	}
	return 0;
}

int d[310][310];
int executeDinic() {
	int totalFlow = 0;
	while (makeLevelGraph()) {
		fill(work.begin(), work.end(), 0);
		while (1) {
			int flow = dfs(startVertex, INF);
			if (!flow) break;
			totalFlow += flow;
		}
	}
	for (int i = startVertex; i <= endVertex; i++) {
		for (auto next : edges[i])
			if (next.cap > 0)
				d[i][next.v] = 1;
	}
	for (int i = startVertex; i <= endVertex; i++) {
		for (int j = startVertex; j <= endVertex; j++) {
			for (int k = startVertex; k <= endVertex; k++) {
				if (d[j][i] && d[i][k]) {
					d[j][k] = 1;
				}
			}
		}
	}
	return totalFlow;
}


vector<pair<int, int>> inp;

void input() {
	ans = 0;
	memset(d, 0, sizeof(d));
	scanf("%d %d", &N, &M);
	startVertex = 1;
	endVertex = N;
	numberOfVertex = endVertex + 1;
	makeEdges();
	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &a, &b, &c);
		inp.push_back({ a,b });
		addEdge(a, b, c);
	}
}
int main() {
	scanf("%d", &K);
	for (int i = 0; i < K; i++) {

		input();
		executeDinic();
		for (auto next : inp) {
			if (!d[next.first][next.second])
				ans++;
		}

		printf("%d\n", ans);
		inp.clear();

	}
}