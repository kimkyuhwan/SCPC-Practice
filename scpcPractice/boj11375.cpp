#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define INF 10000000

struct Edge {
	int v, cap, rev;
	Edge(int _v, int _cap, int _rev) : v(_v), cap(_cap), rev(_rev) {}
};

vector<int> level, work;
vector < vector<Edge> > edges;
int startVertex, endVertex;
int numberOfVertex, numberOfEdge;
void addEdge(int start, int end, int cap) {
	edges[start].emplace_back(end, cap, edges[end].size());
	edges[end].emplace_back(start, 0, edges[start].size() - 1);
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
			int cap = edge.cap;
			if (level[there] == -1 && cap > 0) {
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
		int thereCapacity = edges[here][i].cap;
		if (level[here] + 1 == level[there] && thereCapacity > 0) {
			int cap = dfs(there, min(currentCap, thereCapacity));
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

void makeEdges() {
	level.resize(numberOfVertex);
	work.resize(numberOfVertex);
	edges.resize(numberOfVertex);
}

void input() {
	int N, M, K, W;
	scanf("%d %d", &N, &M);
	startVertex = 0;
	endVertex = N + M + 1;
	numberOfVertex = endVertex + 1;
	makeEdges();
	for (int i = 1; i <= N; i++) {
		scanf("%d", &K);
		addEdge(startVertex, i, 1);
		for (int j = 0; j < K; j++) {
			scanf("%d", &W);
			addEdge(i, W + N, 1);
		}
	}
	for (int i = 1; i <= M; i++) {
		addEdge(i + N, endVertex, 1);
	}
}

int main() {
	input();
	int sol = executeDinic();
	printf("%d\n", sol);
}