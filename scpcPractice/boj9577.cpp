#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
#define TIME 0
#define TORRENT 120
struct Edge {
	int v, cap, rev;
	Edge(int _v, int _cap, int _rev) : v(_v), cap(_cap), rev(_rev) {}
};

vector<vector<Edge> > edges;
vector<int> level, work;
int N, M, ttime;
int startVertex=0, endVertex=230, numberOfVertex;

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
		if (thereCap > 0 && level[here] + 1 == level[there]) {
			int cap = dfs(there, min(currentCap, thereCap));
			if (cap > 0) {
				edges[here][i].cap -= cap;
				edges[there][edges[here][i].rev].cap += cap;
				if (here >= TIME && here < TORRENT) {
					ttime = max(ttime, here - TIME);
				}
				return cap;
			}
		}
	}
	return 0;
}




void makeEdges() {
	edges.clear();
	level.clear();
	work.clear();
	edges.resize(numberOfVertex);
	level.resize(numberOfVertex);
	work.resize(numberOfVertex);
}

void addEdge(int start, int end, int cap) {
	edges[start].emplace_back(end, cap, edges[end].size());
	edges[end].emplace_back(start, 0, edges[start].size()-1);
}

void input() {
	int t1, t2, a, q;
	scanf("%d %d", &N, &M);
	numberOfVertex = endVertex + 1;
	makeEdges();
	
	for (int i = 1; i <= 100; i++)
	{
		addEdge(startVertex, TIME + i, 1);
		addEdge(i + TORRENT, endVertex, 1);
	}
	for (int i = 1; i <= M; i++) {
		scanf("%d %d %d", &t1, &t2, &a);
		
		for (int j = 0; j < a; j++) {
			scanf("%d", &q);
			for (int t = t1 + 1; t <= t2; t++) {
				addEdge(t + TIME, q + TORRENT, 1);
			}
		}
	}
}


int solution() {
	int totalFlow = 0;
	ttime = 0;
	while(makeLevelGraph()){
		fill(work.begin(), work.end(), 0);
		while (1) {
			int flow = dfs(startVertex, INF);
			if (!flow) break;
			totalFlow += flow;
			if (totalFlow == N) {
				return ttime;
			}
		}
	}
	return -1;
}


int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		input();
		int ans = solution();
		printf("%d\n", ans);
	}

}