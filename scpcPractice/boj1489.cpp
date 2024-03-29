#include <bits/stdc++.h>
using namespace std;
#define INF 1e9

struct Edge {
	int v, cap, cost, rev;
	Edge(int _v, int _cap, int _cost, int _rev) : v(_v), cap(_cap), cost(_cost), rev(_rev) {}
};

vector<vector<Edge> > edges;
vector<int> isFinish;
vector<int> dist;
vector<int> preVertex, preIndex;
vector<bool> inQ;
int startVertex, endVertex, numberOfVertex;
bool makeSPFA() {
	queue<int> q;
	fill(dist.begin(), dist.end(), -INF);
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
			if (thereCap > 0 && dist[there] < dist[here] + thereCost) {
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
			cost += flow * edges[pre][idx].cost;
			edges[pre][idx].cap -= flow;
			edges[pos][edges[pre][idx].rev].cap += flow;
		}
		totalFlow += flow;
	}
	return cost;
}

void addEdge(int start, int end, int cap, int cost) {
	edges[start].emplace_back(end, cap, cost, edges[end].size());
	edges[end].emplace_back(start, 0, -cost, edges[start].size() - 1);
}

void makeEdges() {
	edges.resize(numberOfVertex);
	dist.resize(numberOfVertex);
	preVertex.resize(numberOfVertex);
	preIndex.resize(numberOfVertex);
	inQ.resize(numberOfVertex);
}

int vA[1010], vB[1010];
void input() {
	int N;
	scanf("%d", &N);
	startVertex = N + N;
	endVertex = startVertex + 1;
	numberOfVertex = endVertex + 1;
	makeEdges();
	for (int i = 0; i < N; i++) {
		scanf("%d", &vA[i]);
		addEdge(startVertex, i, 1, 0);
	}
	for (int i = 0; i < N; i++) {
		scanf("%d", &vB[i]);
		addEdge(i+N, endVertex, 1, 0);
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (vA[i] > vB[j]) {
				addEdge(i, j+N,1, 2);
			}
			else if (vA[i] == vB[j]) {
				addEdge(i, j+N, 1, 1);
			}
			else {
				addEdge(i, j + N, 1, 0);
			}
		}
	}
}

int main() {
	input();
	int ans = executeMCMF();
	printf("%d\n", ans);
}