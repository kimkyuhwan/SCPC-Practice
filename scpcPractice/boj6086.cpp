#include <vector>
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
#define INF 1987654321
struct Edge {
	int v, cap, rev;
	Edge(int _v, int _cap, int _rev) : v(_v), cap(_cap), rev(_rev) {}
};
vector<vector<Edge> > edges;
int NumberOfVertex, NumberOfEdge;
int StartVertex, EndVertex;
vector<int> dist, work;

void addEdge(int start, int end, int capacity) {
	edges[start].emplace_back(end, capacity, edges[end].size());
	edges[start].emplace_back(start, 0, edges[start].size() - 1);
}

bool makeLevelGraph() {
	fill(dist.begin(), dist.end(), -1);
	queue<int> q;
	q.push(StartVertex);
	dist[StartVertex] = 0;
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		for (Edge hereEdge : edges[here]) {
			int there = hereEdge.v;
			int capacity = hereEdge.cap;
			if (dist[there] == -1 && capacity > 0)
			{
				dist[there] = dist[here] + 1;
				q.push(there);
			}
		}
	}
	return dist[EndVertex] != -1;
}

int dfs(int here, int currentCapacity) {
	if (here == EndVertex) return currentCapacity;

	for (int &i = work[here]; i < edges[here].size(); i++) {
		int there = edges[here][i].v;
		int thereCapacity = edges[here][i].cap;
		if (dist[here] + 1 == dist[there] && thereCapacity > 0) {
			int cap = dfs(there, min(currentCapacity, thereCapacity));
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
			int flow = dfs(StartVertex, INF);
			if (!flow) break;
			ret += flow;
		}
	}
	return ret;
}

void makeEdges() {
	edges.resize(NumberOfVertex);
	dist.resize(NumberOfVertex);
	work.resize(NumberOfVertex);
}

void input() {
	NumberOfVertex = 60;
	scanf("%d", &NumberOfEdge);
	makeEdges();
	StartVertex = 0;
	EndVertex = 25;
	int F;
	char a, b;
	for (int i = 0; i<NumberOfEdge; i++) {
		scanf(" %c %c %d", &a, &b, &F);
		int x, y;
		if (a >= 'A' && a <= 'Z') {
			x = a - 'A';
		}
		else {
			x = a - ('a' - 26);
		}
		if (b >= 'A' && b <= 'Z') {
			y = b - 'A';
		}
		else {
			y = b - ('a' - 26);
		}
		addEdge(x, y, F);
		addEdge(y, x, F);
	}


}

int main() {
	input();
	makeEdges();
	int sol = executeDinic();
	printf("%d\n", sol);
}