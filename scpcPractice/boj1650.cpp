#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
struct Edge {
	int v, cap, cost, rev;
	Edge(int _v, int _cap, int _cost, int _rev) : v(_v), cap(_cap), cost(_cost), rev(_rev) {}
};


int N, M;
int P, Q, L;
int startVertex, endVertex, numberOfVertex;

vector<vector<Edge> > edges;
vector<int> dist, preVertex, preIndex;
vector<bool> inQ;

bool makeSPFA() {
	fill(dist.begin(), dist.end(), INF);
	fill(preVertex.begin(), preVertex.end(), -1);
	fill(preIndex.begin(), preIndex.end(), -1);
	fill(inQ.begin(), inQ.end(), false);
	queue<int> q;
	q.push(startVertex);
	dist[startVertex] = 0;
	inQ[startVertex] = true;
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		inQ[here] = false;
		for (int i = 0; i < edges[here].size(); i++) {
			int there = edges[here][i].v;
			int thereCap = edges[here][i].cap;
			int thereCost = edges[here][i].cost;
			if (thereCap > 0 && dist[there] > dist[here] + thereCost) {
				preVertex[there] = here;
				preIndex[there] = i;
				dist[there] = dist[here] + thereCost;
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
			edges[pre][idx].cap -= flow;
			edges[pos][edges[pre][idx].rev].cap += flow;
			cost += edges[pre][idx].cost*flow;
		}
	}
	return cost;
}


void addEdge(int start, int end, int cap, int cost) {
	edges[start].emplace_back(end, cap, cost, edges[end].size());
	edges[end].emplace_back(start, 0, -cost, edges[start].size()-1);
}

void makeEdges() {
	edges.resize(numberOfVertex);
	dist.resize(numberOfVertex);
	preVertex.resize(numberOfVertex);
	preIndex.resize(numberOfVertex);
	inQ.resize(numberOfVertex);
}

void input() {
	scanf("%d %d", &N, &M);
	startVertex = 0;
	endVertex = N+1;
	numberOfVertex = endVertex + 1 + M*2;
	makeEdges();
	addEdge(startVertex, 1, 2, 0);
	addEdge(N, endVertex, 2, 0);
	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &P, &Q, &L);
		addEdge(P, Q, 1, L);
		addEdge(Q, P, 1, L);
	}
}


int main() {
	input();
	int ans = executeMCMF();
	printf("%d\n", ans);
}