#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
struct Edge {
	int v, cap, rev;
	Edge(int _v, int _cap, int _rev) : v(_v), cap(_cap), rev(_rev) {}
};

vector<vector <Edge> > edges;
vector<int> level, work;

int n, m;
int s, e;
int a, b;
int cost;
int startVertex, endVertex, numberOfVertex;

bool makeLevelGraph() {
	queue<int> q;
	fill(level.begin(), level.end(), -1);
	level[startVertex] = 0;
	q.push(startVertex);
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		for (int i = 0; i < edges[here].size(); i++) {
			int there = edges[here][i].v;
			int thereCap = edges[here][i].cap;
			if (thereCap > 0 && level[there] == -1) {
				level[there] = level[here] + 1;
				q.push(there);
			}
		}
	}
	return level[endVertex] != -1;

}
int dfs(int here, int currentCap) {
	if (here == endVertex) return currentCap;
	for (int &i = work[here]; i < edges[here].size(); i++) {
		int there = edges[here][i].v;
		int thereCap = edges[here][i].cap;
		if (thereCap > 0 && level[there] == level[here] + 1) {
			int cap = dfs(there, min(currentCap, thereCap));
			if (cap > 0) {
				edges[here][i].cap -= cap;
				edges[there][edges[here][i].rev].cap += cap;
				return cap;
			}
		}
	}
	return 0;
}

int executeMCMF() {

	int totalFlow = 0;
	vector<int> sol;
	while (makeLevelGraph()) {
		fill(work.begin(), work.end(), 0);
		while (1) {
			int flow = dfs(startVertex, INF);
			if (!flow) break;
			totalFlow += flow;
		}
	}
	return totalFlow;
}

void addEdge(int start, int end, int cap) {
	edges[start].emplace_back(end, cap, edges[end].size());
	edges[end].emplace_back(start, 0, edges[start].size() - 1);
}

void makeEdges() {
	edges.resize(numberOfVertex);
	level.resize(numberOfVertex);
	work.resize(numberOfVertex);
}


void input() {
	scanf("%d %d", &n, &m);
	scanf("%d %d", &s, &e);
	numberOfVertex = n * 2 + 2;
	startVertex = s * 2;
	endVertex = e * 2+1;
	makeEdges();
	for (int i = 1; i <= n; i++) {
		scanf("%d", &cost);
		addEdge(i * 2, i * 2 + 1, cost);
	}
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		addEdge(a * 2 + 1, b * 2, INF);
		addEdge(b * 2 + 1, a * 2, INF);
	}
}
void solution() {
	vector<bool> check(n * 2 + 2);
	queue<int> que;
	que.push(s * 2);
	check[s * 2] = true;
	int tmp = 0;
	while (!que.empty()) {
		int here = que.front();
		que.pop();
		for (int i = 0; i < edges[here].size(); i++) {
			int next = edges[here][i].v;
			if (!check[next] && edges[here][i].cap) {
				check[next] = true;
				que.push(next);
			}
		}
	}
	for (int i = 1; i <= n; i ++) {
		if (check[i*2] && !check[i*2 + 1])
			cout << i << " ";
	}
}

int main() {
	input();
	executeMCMF();
	solution();
}