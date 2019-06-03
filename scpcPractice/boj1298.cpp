#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
struct Edge {
	int v, cap, rev;
	Edge(int _v, int _cap, int _rev) : v(_v), cap(_cap), rev(_rev) {}
};
int startVertex, endVertex, numberOfVertex;
vector<vector<Edge> > edges;
vector<int> level, work;

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
			if (level[there] == -1 && thereCap > 0) {
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

int executeDinic() {
	int ret = 0;
	while (makeLevelGraph()) {
		fill(work.begin(), work.end(), 0);
		while (1) {
			int flow = dfs(startVertex, INF);
			if (!flow) break;
			ret += flow;
		}
	}
	return ret;
}


void addEdge(int start, int end, int cap) {
	edges[start].emplace_back(end, cap, edges[end].size());
	edges[end].emplace_back(start, 0, edges[start].size()-1);
}

void makeEdges() {
	edges.resize(numberOfVertex);
	level.resize(numberOfVertex);
	work.resize(numberOfVertex);
}

void input() {
	int N, M, a, b;
	scanf("%d %d", &N, &M);
	startVertex = N + N;
	endVertex = startVertex + 1;
	numberOfVertex = endVertex + 1;
	makeEdges();
	for (int i = 0; i < N; i++) {
		addEdge(startVertex, i, 1);
		addEdge(i+N, endVertex, 1);
	}
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &a, &b);
		a--, b--;
		addEdge(a, b + N, 1);
	}
}

int main() {
	input();
	int ans = executeDinic();
	printf("%d\n", ans);
	return 0;
}