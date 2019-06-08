#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
#define START_RULE 100

struct Edge {
	int v, cap, cost, rev;
	Edge(int _v, int _cap, int _cost, int _rev) : v(_v), cap(_cap), cost(_cost), rev(_rev) {}
};

vector<vector <Edge> > edges;
int startVertex, endVertex, sum;
int numberOfVertex;
vector<int> dist, preVertex, preIndex;
vector<bool> inQ;


bool makeSPFA() {
	queue<int> q;
	fill(dist.begin(), dist.end(), INF);
	fill(preVertex.begin(), preVertex.end(), -1);
	fill(preIndex.begin(), preIndex.end(), -1);
	fill(inQ.begin(), inQ.end(), false);
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
bool isNotPossible = false;
vector<int> executeMCMF() {
	int totalFlow = 0, cost = 0;
	vector<int> ret;
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
			int temp = edges[pre][idx].cost;
			if (temp > 0) {
				ret.push_back(pos);
			}
			cost += edges[pre][idx].cost*flow;
		}
		totalFlow += flow;
	}
	if (totalFlow != sum) {
		isNotPossible = true;
	}
	return ret;
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


void input() {
	int N, M, K, val, cost;
	scanf("%d", &N);
	startVertex = 0;
	endVertex = 201;
	numberOfVertex = endVertex + 1;
	makeEdges();
	bool isExist[110] = { false, };
	for (int i = 0; i < N; i++) {
		scanf("%d", &val);
		isExist[val] = true;
	}
	for (int i = 1; i <= 100; i++) {
		if(isExist[i]) addEdge(startVertex, i, 1, 0);
		else addEdge(startVertex, i, 1, i);
	}
	scanf("%d", &M);
	for (int i = 1; i <= M; i++) {
		scanf("%d %d", &cost, &K);
		addEdge(START_RULE+i, endVertex, cost, 0);
		sum += cost;
		for (int j = 0; j < K; j++) {
			scanf("%d", &val);
			addEdge(val, START_RULE + i, 1, 0);
		}
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	input();
	vector<int> ans = executeMCMF();
	if (isNotPossible) {
		puts("-1");
		return 0;
	}
	sort(ans.begin(), ans.end());
	printf("%d\n", ans.size());
	for (int i = 0; i < ans.size(); i++) {
		printf("%d ", ans[i]);
	}

}