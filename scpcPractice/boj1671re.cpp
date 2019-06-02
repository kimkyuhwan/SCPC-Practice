#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
int N;

struct Edge {
	int v, cap, rev;
	Edge(int _v, int _cap, int _rev) : v(_v), cap(_cap), rev(_rev) {}
};

struct Shark {
	int sz, speed, intell;
	Shark(int _sz, int _speed, int _intell) : sz(_sz), speed(_speed), intell(_intell) {}
};


vector<vector<Edge> > edges;
vector<Shark> sharks;

int startVertex, endVertex;
int numberOfVertex;

vector<int> level, work;

bool makeLevelGraph() {
	queue<int> q;
	fill(level.begin(), level.end(), -1);
	level[startVertex] = 0;
	q.push(startVertex);
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		for (Edge edge : edges[here]) {
			int there = edge.v;
			int thereCap = edge.cap;
			if (level[there] == -1 && thereCap > 0) {
				level[there] = level[here] + 1;
				q.push(there);
			}
		}
	}
	return level[endVertex] != -1;
}

int dfs(int here, int currentCap) {
	if (here == endVertex) return currentCap;
	for (int &i=work[here]; i < edges[here].size(); i++) {
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


int executeDinic() {
	int ret = 0;
	while (makeLevelGraph()) {
		fill(work.begin(), work.end(), 0);
		while (1) {
			int flow = dfs(startVertex,INF);
			if (!flow) break;
			ret += flow;
		}
	}
	return ret;
}

bool isPossibleEat(int a, int b) {
	Shark A = sharks[a];
	Shark B = sharks[b];
	if (A.sz == B.sz && A.speed == B.speed && A.intell == B.intell && a < b) {
		return false;
	}
	return A.sz >= B.sz && A.speed >= B.speed && A.intell >= B.intell;
}

void addEdge(int start, int end, int cap) {
	edges[start].emplace_back(end, cap, edges[end].size());
	edges[end].emplace_back(start, 0, edges[start].size()-1);
}

void makeEdges() {
	edges.resize(numberOfVertex);
	level.resize(numberOfVertex);
	work.resize(numberOfVertex);
}


void input() {
	int sz, speed, intell;
	scanf("%d", &N);
	startVertex = N+N;
	endVertex = N + N + 1;
	numberOfVertex = endVertex+1;
	makeEdges();
	for (int i = 0; i < N; i++) {
		scanf("%d %d %d", &sz, &speed, &intell);
		addEdge(startVertex, i, 2);
		addEdge(i + N, endVertex, 1);
		sharks.emplace_back(sz, speed, intell);
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == j) continue;
			if (isPossibleEat(i, j)) {
				addEdge(i, j + N, 1);
			}
		}
	}
}

int main() {
	input();
	int canEat = executeDinic();
	printf("%d\n", N - canEat);
}