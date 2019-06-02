#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
struct Edge {
	int v, cap, cost, rev;
	Edge(int _v, int _cap, int _cost, int _rev) : v(_v), cap(_cap), cost(_cost), rev(_rev) {}
};


int startVertex, endVertex;
int numberOfVertex;

vector<vector<Edge> > edges;
vector<int> dist, preVertex, preIndex;
vector<bool> inQ;

bool makeSPFA() {
	queue<int> q;
	fill(dist.begin(), dist.end(), INF);
	fill(preVertex.begin(), preVertex.end(), -1);
	fill(preIndex.begin(), preIndex.end(), -1);
	fill(inQ.begin(), inQ.end(), false);
	q.push(startVertex);
	dist[startVertex] = 0;
	inQ[startVertex] = true;
	while (!q.empty()) {
		int here = q.front(); q.pop();
		inQ[here] = false;
		for (int i = 0; i < edges[here].size(); i++) {
			int there = edges[here][i].v;
			int thereCap = edges[here][i].cap;
			int thereDist = edges[here][i].cost;
			if (thereCap > 0 && dist[there] > dist[here] + thereDist) {
				dist[there] = dist[here] + thereDist;
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


pair<int, int> executeMCMF() {
	int totalFlow=0, cost = 0;
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
			cost += flow*edges[pre][idx].cost;
			edges[pre][idx].cap -= flow;
			edges[pos][edges[pre][idx].rev].cap += flow;
		}
		totalFlow += flow;
	}
	return { totalFlow,cost };
}


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

int C[110][110], D[110][110];
void input() {
	int N, M, K;
	scanf("%d %d", &N, &M);
	startVertex = N + M + 1;
	endVertex = startVertex + 1;
	numberOfVertex = endVertex + 1;
	makeEdges();
	for (int i = 0; i < N; i++) {
		scanf("%d", &K);
		addEdge(startVertex, i, K, 0);
	}
	for (int i = 0; i < M; i++) {
		scanf("%d", &K);
		addEdge(i+N, endVertex, K, 0);
	}
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &C[i][j]);
		}
	}
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &D[i][j]);
		}
	}
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			addEdge(j, i + N, C[i][j], D[i][j]);
		}
	}
}
int main() {
	input();
	pair<int, int> ans = executeMCMF();
	printf("%d\n%d\n", ans.first, ans.second);

}