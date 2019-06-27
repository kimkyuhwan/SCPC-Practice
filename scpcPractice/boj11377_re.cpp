#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
struct Edge {
	int v, cap, rev;
	Edge(int _v, int _cap, int _rev) : v(_v), cap(_cap), rev(_rev) {}
};

int startVertex, portalVertex, endVertex, numberOfVertex;
vector<vector<Edge> > edges;
vector<int> level, work;

void addEdge(int s, int e, int cap) {
	edges[s].emplace_back(e, cap, edges[e].size());
	edges[e].emplace_back(s, 0, edges[s].size()-1);
}

void makeEdges() {
	edges.resize(numberOfVertex);
	level.resize(numberOfVertex);
	work.resize(numberOfVertex);
}

int N, M, K, W, w;
void input() {
	scanf("%d %d %d", &N, &M, &K);
	startVertex = 0;
	portalVertex = N + M + 1;
	endVertex = N + M + 2;
	numberOfVertex = endVertex + 1;
	makeEdges();
	addEdge(startVertex, portalVertex, K);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &W);
		addEdge(startVertex, i, 1);
		addEdge(portalVertex, i, 1);
		for (int j = 0; j < W; j++) {
			scanf("%d", &w);
			addEdge(i, N + w, 1);
		}
	}
	for (int i = 1; i <= M; i++) {
		addEdge(N + i, endVertex, 1);
	}
}

bool makeLevelGraph() {
	queue<int> q;
	q.push(startVertex);
	fill(level.begin(), level.end(), -1);
	level[startVertex] = 0;
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
		if (level[there] == level[here] + 1 && thereCap > 0) {
			int minCap = dfs(there, min(currentCap,thereCap));
			if(minCap > 0){
				edges[here][i].cap -= minCap;
				edges[there][edges[here][i].rev].cap += minCap;
				return minCap;
			}
		}
	}
	return 0;
}

int executeDinic() {
	int ret = 0;
	while (makeLevelGraph()) {
		fill(work.begin(), work.end(), 0);
		while (true) {
			int flow = dfs(startVertex, INF);
			if (!flow) break;
			ret += flow;
		}
	}
	return ret;
}


int main()
{
	input();
	int ans = executeDinic();
	printf("%d\n", ans);
}