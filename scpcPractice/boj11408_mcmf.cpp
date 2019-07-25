#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
int N, M, K;
int money, work;
int startVertex, endVertex, numberOfVertex;
vector<int> preVertex, preIndex, dist;
vector<bool> inQ;
struct Edge {
	int v, cap, cost, rev;
	Edge(int v, int cap, int cost, int rev) : v(v), cap(cap), cost(cost), rev(rev) {}
};
vector<vector<Edge> > edges;

void makeEdges() {
	edges.resize(numberOfVertex);
	preVertex.assign(numberOfVertex, -1);
	preIndex.assign(numberOfVertex, -1);
	dist.assign(numberOfVertex, -1);
	inQ.assign(numberOfVertex, false);
}

void addEdge(int start, int end, int cap, int cost) {
	edges[start].emplace_back(end, cap, cost, edges[end].size());
	edges[end].emplace_back(start, 0, -cost, edges[start].size() - 1);
}

void input() {
	scanf("%d %d", &N, &M);
	startVertex = 0;
	endVertex = N + M + 1;
	numberOfVertex = endVertex + 1;
	makeEdges();
	for (int i = 1; i <= N; i++) {
		scanf("%d", &K);
		addEdge(startVertex, i, 1, 0);
		for (int j = 0; j < K; j++) {
			scanf("%d %d", &work, &money);
			addEdge(i, N+work, 1, money);
		}
	}
	for (int i = 1; i <= M; i++) {
		addEdge(i + N, endVertex, 1, 0);
	}
}

bool makeSPFA() {
	fill(preVertex.begin(), preVertex.end(), -1);
	fill(preIndex.begin(), preIndex.end(), -1);
	fill(dist.begin(), dist.end(), INF);
	fill(inQ.begin(), inQ.end(), false);
	queue<int> q;
	q.push(startVertex);
	inQ[startVertex] = true;
	dist[startVertex] = 0;
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		inQ[here] = false;
		for (int i = 0; i < edges[here].size(); i++) {
			int there = edges[here][i].v;
			int thereCap = edges[here][i].cap;
			int thereCost = edges[here][i].cost;
			if (thereCap>0 && dist[there] > dist[here] + thereCost) {
				preVertex[there] = here;
				preIndex[there] = i;
				dist[there] = dist[here] + thereCost;
				if (!inQ[there]) {
					inQ[there] = true;
					q.push(there);
				}
			}
		}
	}
	return preVertex[endVertex] != -1;
}

pair<int,int> executeMCMF() {
	int totalCost = 0, totalFlow = 0;
	while (makeSPFA()) {
		int flow = INF;
		for (int i = endVertex; i != startVertex; i = preVertex[i]) {
			int pre = preVertex[i];
			int idx = preIndex[i];
			flow = min(flow, edges[pre][idx].cap);
		}
		for (int i = endVertex; i != startVertex; i = preVertex[i]) {
			int pre = preVertex[i];
			int idx = preIndex[i];
			edges[pre][idx].cap -= flow;
			edges[i][edges[pre][idx].rev].cap += flow;
			totalCost += edges[pre][idx].cost*flow;
		}
		if (!flow) break;
		totalFlow += flow;

	}
	return{ totalFlow,totalCost };
}

int main() {
	input();
	pair<int,int> ans = executeMCMF();
	printf("%d\n%d\n", ans.first,ans.second);
}