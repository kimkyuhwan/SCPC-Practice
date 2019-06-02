#include <bits/stdc++.h>
using namespace std;
#define INF 1e9

struct Edge {
	int v, cap, cost, rev;
	Edge(int _v, int _cap, int _cost, int _rev) : v(_v), cap(_cap), cost(_cost), rev(_rev) {}
};

int V, E, numberOfVertex;
int startVertex, endVertex;
vector<vector<Edge> > edges;
vector<int> dist, preVertex, preIndex;
vector<bool> inQ;

bool makeSPFA() {
	queue<int> q;
	fill(dist.begin(), dist.end(), INF);
	fill(preVertex.begin(), preVertex.end(), -1);
	fill(preIndex.begin(), preIndex.end(), -1);
	fill(inQ.begin(), inQ.end(), false);

	dist[startVertex] = 0;
	q.push(startVertex);
	inQ[startVertex] = true;
	while (!q.empty()) {
		int here = q.front(); q.pop();
		inQ[here] = false;
		for (int i = 0; i < edges[here].size(); i++) {
			int there = edges[here][i].v;
			int thereCap = edges[here][i].cap;
			int thereCost = edges[here][i].cost;
			if (thereCap > 0 && dist[there] > dist[here] + thereCost) {
				dist[there] = dist[here] + thereCost;
				preVertex[there] = here;
				preIndex[there] = i;
				if (!inQ[there]) {
					q.push(there);
					inQ[there] = true;
				}
			}
		}
	}
	return preVertex[endVertex] != -1;
}

int executeMCMF() {
	int totalFlow = 0, cost = 0;
	while (makeSPFA()) {
		int flow = INF;
		for (int pos = endVertex; pos != startVertex; pos = preVertex[pos]) {
			int pre = preVertex[pos];
			int idx = preIndex[pos];
			flow = min(flow, edges[pre][idx].cap);
		}

		for (int pos = endVertex; pos != startVertex; pos = preVertex[pos]) {
			int pre = preVertex[pos];
			int idx = preIndex[pos];
			cost += edges[pre][idx].cost*flow;
			edges[pre][idx].cap -= flow;
			edges[pos][edges[pre][idx].rev].cap += flow;
		}
		totalFlow += flow;
		if (totalFlow >= 2) {
			break;
		}
	}
	return cost;
}

void makeEdges() {
	edges.clear();
	dist.clear();
	preVertex.clear();
	preIndex.clear();
	inQ.clear();
	edges.resize(numberOfVertex);
	dist.resize(numberOfVertex);
	preVertex.resize(numberOfVertex);
	preIndex.resize(numberOfVertex);
	inQ.resize(numberOfVertex);
}

void addEdge(int start, int end, int cap, int cost) {
	edges[start].emplace_back(end, cap, cost, edges[end].size());
	edges[end].emplace_back(start, 0, -cost, edges[start].size() - 1);
}

void input() {
	int a, b, c;
	startVertex = 0;
	endVertex = V*2+1;
	numberOfVertex = endVertex + 1;
	makeEdges();
	addEdge(startVertex, 1, 2, 0);
	addEdge(V, endVertex, 2, 0);

	for (int i = 1; i <= V; i++) {
		if (i == 1 || i == V) {
			addEdge(i, i + V, 2, 0);
		}
		else {
			addEdge(i, i + V, 1, 0);
		}
	}


	for (int i = 0; i < E; i++) {
		scanf("%d %d %d", &a, &b, &c);
		addEdge(a+V, b, 1, c);
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	while (scanf("%d %d", &V, &E) != EOF) {
		input();
		int result = executeMCMF();
		printf("%d\n", result);
	}
}