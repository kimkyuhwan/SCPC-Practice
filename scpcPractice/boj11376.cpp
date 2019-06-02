#include <vector>
#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;
#define INF 1987654321
struct Edge {
	int v, cap, rev;
	Edge(int _v, int _cap, int _rev) : v(_v), cap(_cap), rev(_rev){}
};

vector<vector<Edge> > edges;
int startVertex, endVertex;
int numberOfVertex;
vector<int> dist, work;
void addEdge(int start, int end, int cap) {
	edges[start].emplace_back(end, cap, edges[end].size());
	edges[end].emplace_back(start, 0, edges[start].size()-1);
}

bool makeLevelGraph() {
	queue<int> q;
	fill(dist.begin(), dist.end(), -1);
	dist[startVertex] = 0;
	q.push(startVertex);
	while (!q.empty()) {
		int here = q.front(); q.pop();
		for (Edge edge : edges[here]) {
			int there = edge.v;
			int thereCap = edge.cap;
			if (dist[there] == -1 && thereCap > 0) {
				dist[there] = dist[here] + 1;
				q.push(there);
			}
		}
	}
	return dist[endVertex] != -1;
}

int dfs(int here, int currentCapacity) {
	if (here == endVertex) return currentCapacity;
	for (int &i = work[i]; i < edges[here].size(); i++)
	{
		int there = edges[here][i].v;
		int thereCap = edges[here][i].cap;
		if (dist[here]+1 == dist[there] && thereCap > 0) {
			int cap = dfs(there, min(currentCapacity, thereCap));
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
			int flow= dfs(startVertex, INF);
			if (!flow) break;
			ret += flow;
		}
	}
	return ret;
}

void makeEdges() {
	edges.resize(numberOfVertex);
	dist.resize(numberOfVertex);
	work.resize(numberOfVertex);
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
		addEdge(startVertex, i, 2);
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
	return 0;
}