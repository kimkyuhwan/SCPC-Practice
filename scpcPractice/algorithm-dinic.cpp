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
vector<int> level, work;

void addEdge(int start, int end, int capacity) {
	edges[start].emplace_back(end, capacity, edges[end].size());
	edges[start].emplace_back(start, 0, edges[start].size()-1);
}

bool makeLevelGraph() {
	fill(level.begin(), level.end(), -1);
	queue<int> q;
	q.push(StartVertex);
	level[StartVertex] = 0;
	while (!q.empty()) {
		int here = q.front();
		q.pop();	
		for (Edge hereEdge : edges[here]) {
			int there = hereEdge.v;
			int capacity = hereEdge.cap;
			if (level[there] == -1 && capacity > 0)
			{
				level[there] = level[here] + 1;
				q.push(there);
			}
		}
	}
	return level[EndVertex] != -1;
}

int dfs(int here, int currentCapacity) {
	if (here == EndVertex) return currentCapacity;

	for (int &i = work[here]; i < edges[here].size(); i++) {
		int there = edges[here][i].v;
		int thereCapacity = edges[here][i].cap;
		if (level[here] + 1 == level[there] && thereCapacity > 0) {
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
	level.resize(NumberOfVertex);
	work.resize(NumberOfVertex);
}

void input() {

}

int main() {
	//input();
	makeEdges();
	int sol=executeDinic();
	printf("%d\n", sol);
}