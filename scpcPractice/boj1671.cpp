#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define INF 1987654321
struct Edge {
	int v, cap, rev;
	Edge(int _v,int _cap, int _rev) : v(_v),cap(_cap),rev(_rev) {}
};

struct Shark {
	int sz, speed, intell;
	Shark(int _sz, int _speed, int _intell) : sz(_sz), speed(_speed), intell(_intell) {}
};

vector<vector<Edge> > edges;
vector<Shark> sharks;
vector<int> dist, work;
int startVertex, endVertex;
int numberOfVertex;
int N;

bool makeLevelGraph() {
	queue<int> q;
	fill(dist.begin(), dist.end(), -1);
	q.push(startVertex);
	dist[startVertex] = 0;
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		for (Edge edge : edges[here]) {
			int there = edge.v;
			int thereCap = edge.cap;
			if (dist[there] == -1 && thereCap > 0) {
				dist[there] = dist[here] + 1;
				q.push(there);
			}
		}
	}
	return dist[endVertex] != -1;
}

int dfs(int here, int currentCap) {
	if (here == endVertex) return currentCap;
	for (int &i = work[here]; i < edges[here].size(); i++) {
		int there = edges[here][i].v;
		int thereCap = edges[here][i].cap;
		if (dist[here] + 1 == dist[there] && thereCap > 0) {
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
			int flow = dfs(startVertex, INF);
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
	return (A.sz >= B.sz) && (A.speed >= B.speed) && (A.intell >= B.intell) ;
}

void makeEdges() {
	edges.resize(numberOfVertex);
	dist.resize(numberOfVertex);
	work.resize(numberOfVertex);
}

void addEdges(int start, int end, int cap) {
	edges[start].emplace_back(end, cap, edges[end].size());
	edges[end].emplace_back(start, 0, edges[start].size()-1);
}

void input() {
	int L, S, I;
	scanf("%d", &N);
	startVertex = N+N;
	endVertex = N+N + 1;
	numberOfVertex = endVertex + 1;
	makeEdges();
	for (int i = 0; i < N; i++) {
		scanf("%d %d %d", &L, &S, &I);
		sharks.emplace_back(L, S, I);
		addEdges(startVertex, i, 2);
		addEdges(i + N, endVertex, 1);
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == j) continue;
			if (isPossibleEat(i, j)) {
				addEdges(i, j + N, 1);
			}
		}
	}
}

int main() {
	input();
	int canEat = executeDinic();
	printf("%d\n", N-canEat);
	return 0;
}