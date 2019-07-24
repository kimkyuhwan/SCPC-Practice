#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
int N, M;
int work, W;
int startVertex, endVertex, numberOfVertex;
vector<int> wk, level;
struct Edge {
	int v, cap, rev;
	Edge(int v, int cap, int rev) : v(v), cap(cap), rev(rev) {}
};
vector<vector<Edge> > edges;

void makeEdges() {
	edges.resize(numberOfVertex);
	level.resize(numberOfVertex);
	wk.resize(numberOfVertex);
}


void addEdge(int start, int end, int cap) {
	edges[start].emplace_back(end, cap, edges[end].size());
	edges[end].emplace_back(start, 0, edges[start].size()-1);
}

bool makeLevelGraph() {
	fill(level.begin(), level.end(), -1);
	queue<int> q;
	q.push(startVertex);
	level[startVertex] = 0;
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

int dfs(int here, int hereCap) {
	if (here == endVertex) return hereCap;
	for (int &i = wk[here]; i < edges[here].size(); i++) {
		int there = edges[here][i].v;
		int thereCap = edges[here][i].cap;
		if (thereCap > 0 && level[there]==level[here]+1) {
			int cap = dfs(there, min(hereCap, thereCap));
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
		fill(wk.begin(), wk.end(), 0);
		while (true) {
			int flow = dfs(startVertex, INF);
			if (!flow) break;
			ret += flow;
		}
	}
	return ret;
}




int main() {
	scanf("%d %d", &N, &M);
	endVertex = N + M + 1;
	numberOfVertex = endVertex + 1;
	makeEdges();
	for (int i = 1; i <= N; i++) {
		scanf("%d", &W);
		addEdge(startVertex, i, 1);
		for (int j = 0; j < W; j++) {
			scanf("%d", &work);
			addEdge(i, N + work, 1);
		}
	}
	for (int i = 1; i <= M; i++) {
		addEdge(N + i, endVertex, 1);
	}
	int ans = executeDinic();
	printf("%d\n", ans);
}