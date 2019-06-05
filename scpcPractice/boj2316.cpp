#include <bits/stdc++.h>
using namespace std;
#define INF 1e9

struct Edge {
	int v, cap, rev;
	Edge(int _v, int _cap, int _rev) : v(_v), cap(_cap), rev(_rev) {}
};

vector<vector<Edge> > edges;
vector<int> level, work;
int startVertex, endVertex, numberOfVertex;


void addEdge(int start, int end, int cap) {
	edges[start].emplace_back(end, cap, edges[end].size());
	edges[end].emplace_back(start, 0, edges[start].size()-1);
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
	return totalFlow;
}

void makeEdges() {
	edges.resize(numberOfVertex);
	level.resize(numberOfVertex);
	work.resize(numberOfVertex);
}

void input() {
	int N, P, a, b;
	scanf("%d %d", &N, &P);

	startVertex = 1 * 2;
	endVertex = 2 * 2 + 1;
	numberOfVertex = N * 2 + 2;
	makeEdges();

	addEdge(1 * 2, 1 * 2 + 1, INF);
	addEdge(2 * 2, 2 * 2 + 1, INF);
	for (int i = 3; i <= N; i++) {
		addEdge(i * 2, i * 2 + 1, 1);
	}
	for (int i = 0; i < P; i++) {
		scanf("%d %d", &a, &b);
		addEdge(a * 2 + 1, b * 2, 1);
		addEdge(b * 2 + 1, a * 2, 1);
	}
}

int main() {
	input();
	int ans = executeDinic();
	printf("%d\n", ans);
	return 0;
}