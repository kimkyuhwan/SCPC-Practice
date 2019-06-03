#include <bits/stdc++.h>
using namespace std;
#define INF 1e9


struct Edge {
	int v, cap, flow, rev;
	Edge(int _v, int _cap, int _rev) : v(_v), cap(_cap), rev(_rev) {}
};

vector<vector<Edge> > edges;
vector<int> level, work;
int N, M, K;
int startVertex, endVertex, portalVertex, numberOfVertex;

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
		if (level[here] + 1 == level[there] && thereCap > 0) {
			if (thereCap > 0) {
				int cap = dfs(there, min(currentCap, thereCap));
				if (cap > 0) {
					edges[here][i].cap -= cap;
					edges[there][edges[here][i].rev].cap += cap;
					return cap;
				}
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

void makeEdges() {
	edges.resize(numberOfVertex);
	level.resize(numberOfVertex);
	work.resize(numberOfVertex);
}

void addEdge(int start, int end, int cap) {
	edges[start].emplace_back(end, cap, edges[end].size());
	edges[end].emplace_back(start, 0, edges[start].size() - 1);
}

void input() {
	scanf("%d %d %d", &N, &M, &K);
	startVertex = N + M;
	endVertex = startVertex + 1;
	portalVertex = endVertex + 1;
	numberOfVertex = portalVertex + 1;

	makeEdges();
	int w = 0, num;

	int visited[1010] = {};
	addEdge(startVertex, portalVertex, K);
	for (int i = 0; i < N; i++) {
		scanf("%d", &w);
		addEdge(startVertex, i, 1);

		for (int j = 0; j < w; j++) {
			scanf("%d", &num);
			num--;
			addEdge(i, num + N, 1);
			if (!visited[num]) {
				visited[num] = 1;
				addEdge(portalVertex, num + N, 1);
			}
		}
	}
	for (int i = 0; i < M; i++) {
		addEdge(i + N, endVertex, 1);
	}
}
int main() {
	freopen("input.txt", "r", stdin);
	input();
	int ret = executeDinic();
	printf("%d\n", ret);
}