#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
struct Edge {
	int v, cap, cost, rev;
	Edge(int _v, int _cap, int _cost, int _rev) : v(_v), cap(_cap), cost(_cost), rev(_rev) {}
};

int startVertex, endVertex, numberOfVertex;

vector<vector<Edge> > edges;
vector<int> dist, preVertex, preIndex;
vector<bool> inQ;

void makeEdges() {
	edges.resize(numberOfVertex);
	dist.resize(numberOfVertex);
	preVertex.resize(numberOfVertex);
	preIndex.resize(numberOfVertex);
	inQ.resize(numberOfVertex);
}

void addEdge(int start, int end, int cap, int cost) {
	edges[start].emplace_back(end, cap, cost, edges[end].size());
	edges[end].emplace_back(start, 0, -cost, edges[start].size()-1);
}


void input() {
	startVertex = 0;
	int black = 1;
	int white = 2;
	endVertex = white + 3 * 1000 + 1;
	numberOfVertex = endVertex + 1;
	makeEdges();
	int b, w;
	addEdge(startVertex, black, 15, 0);
	addEdge(startVertex, white, 15, 0);
	int i = 1;
	while(scanf("%d %d", &b, &w)!=EOF){
		addEdge(black, i * 3, 1, b);
		addEdge(white, i * 3 + 1, 1, w);
		addEdge(i * 3, i * 3 + 2, 1, 0);
		addEdge(i * 3 + 1, i * 3 + 2, 1, 0);
		addEdge(i * 3 + 2, endVertex, 1, 0);
		i++;
	}
}

bool makeSPFA() {
	queue<int> q;
	fill(dist.begin(), dist.end(), -INF);
	fill(preVertex.begin(), preVertex.end(), -1);
	fill(preIndex.begin(), preIndex.end(), -1);
	fill(inQ.begin(), inQ.end(), false);
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
		for (int pos = endVertex; pos != startVertex; pos = preVertex[pos]){
			int pre = preVertex[pos];
			int idx = preIndex[pos];
			flow = min(flow, edges[pre][idx].cap);
		}
		for (int pos = endVertex; pos != startVertex; pos = preVertex[pos]){
			int pre = preVertex[pos];
			int idx = preIndex[pos];
			edges[pre][idx].cap -= flow;
			edges[pos][edges[pre][idx].rev].cap += flow;
			cost += edges[pre][idx].cost*flow;
		}
		totalFlow += flow;
	}
	return cost;
}	


int main() {
	input();
	int ans = executeMCMF();
	printf("%d\n", ans);
}