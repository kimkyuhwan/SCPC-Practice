#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
typedef long long ll;
struct Edge {
	int v, cap, rev;
	Edge(int _v, int _cap, int _rev) : v(_v), cap(_cap), rev(_rev) {}
};

vector<vector<Edge> > edges;
vector<int> ans;
vector<int> level, work;
int a[210][210];
int b[210][210];
int n, m;
int startVertex, endVertex, numberOfVertex;
int newStart, newEnd;

int getVertex(int y, int x) {
	return y*(m + 1) + x;
}
bool makeLevelGraph(int src, int sink) {
	queue<int> q;
	fill(level.begin(), level.end(), -1);
	level[src] = 0;
	q.push(src);
	while (!q.empty()) {
		int here = q.front(); q.pop();
		for (int i = 0; i < edges[here].size(); i++) {
			int there = edges[here][i].v;
			int thereCap = edges[here][i].cap;
			if (thereCap > 0 && level[there] == -1) {
				level[there] = level[here] + 1;
				q.push(there);
			}
		}
	}
	return level[sink] != -1;
}

int dfs(int sink, int here, int currentCap) {
	if (here == sink) return currentCap;
	for (int &i = work[here]; i < edges[here].size(); i++) {
		int there = edges[here][i].v;
		int thereCap = edges[here][i].cap;
		if (thereCap > 0 && level[there] == level[here] + 1) {
			int cap = dfs(sink, there, min(currentCap, thereCap));
			if (cap > 0) {
				edges[here][i].cap -= cap;
				edges[there][edges[here][i].rev].cap += cap;
				return cap;
			}
		}
	}
	return 0;
}

int executeDinic(int src, int sink) {
	int totalFlow = 0, cost = 0;
	while (makeLevelGraph(src, sink)) {
		fill(work.begin(), work.end(), 0);
		while (1) {
			int flow = dfs(sink, src, INF);
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

void addEdgeWithDemand(int src, int sink, int start, int end,int l,int r) {
	addEdge(src, end, l);
	addEdge(start, sink, l);
	if (r - l != 0) {
		addEdge(start, end, r - l);
	}
}

void makeEdges() {
	edges.resize(numberOfVertex);
	level.resize(numberOfVertex);
	work.resize(numberOfVertex);
}

void input() {
	scanf("%d %d", &n, &m);
	startVertex = n + m ;
	endVertex = startVertex + 1;
	newStart = endVertex + 1;
	newEnd = newStart + 1;
	numberOfVertex = newEnd + 1;
	makeEdges();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d.%d", &a[i][j], &b[i][j]);
			if (b[i][j] != 0) {
				addEdgeWithDemand(newStart, newEnd, i, j+n, a[i][j], a[i][j] + 1);
			}
			else {
				addEdgeWithDemand(newStart, newEnd, i, j + n, a[i][j], a[i][j]);
			}
		}
		scanf("%d.%d", &a[i][m], &b[i][m]);
		if (b[i][m] != 0) {
			addEdgeWithDemand(newStart, newEnd, startVertex, i, a[i][m], a[i][m] + 1);
		}
		else {
			addEdgeWithDemand(newStart, newEnd, startVertex, i, a[i][m], a[i][m]);
		}
	}
	for (int i = 0; i < m; i++) {
		scanf("%d.%d", &a[n][i], &b[n][i]);
		if (b[n][i] != 0) {
			addEdgeWithDemand(newStart, newEnd, i + n, startVertex, a[n][i], a[n][i] + 1);
		}
		else {
			addEdgeWithDemand(newStart, newEnd, i + n, startVertex, a[n][i], a[n][i]);
		}
	}

}
int main() {
	input();
	int ans= executeDinic(newStart,newEnd);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int upp = 0;
			for (auto next : edges[i]) {
				if (next.v == j + n)
					if (!next.cap)upp++;
			}
			printf("%d ", a[i][j] + upp);
		}
		int upp = 0;
		for (auto next : edges[startVertex]) {
			if (next.v == i)
				if (!next.cap)upp++;
		}
		printf("%d ", a[i][m] + upp);
		puts("");
	}
	for (int i = 0; i < m; i++) {
		int upp = 0;
		for (auto next : edges[n + i]) {
			if (next.v == startVertex)
				if (!next.cap)upp++;
		}
		printf("%d ", a[n][i] + upp);
	}
}