#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
int testcase;
int H, V, x, y;
char mmap[2010][2010];
char temp[2010];
int owner[2010][2010];
int startVertex, endVertex, numberOfVertex;

struct Edge{
	int v,cap,rev;
	Edge(int _v, int _cap, int _rev) : v(_v), cap(_cap), rev(_rev) {}
};

vector<vector<Edge> > edges;
vector<int> level, work;

bool makeLevelGraph() {
	queue<int> q;
	fill(level.begin(), level.end(), -1);
	level[startVertex] = 0;
	q.push(startVertex);
	while (!q.empty()) {
		int here = q.front(); q.pop();
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
	memset(mmap, 0, sizeof(mmap));
	scanf("%d %d", &H, &V);
	startVertex = H + V;
	endVertex = startVertex + 1;
	numberOfVertex = endVertex + 1;
	makeEdges();
	for (int i = 0; i < H; i++) {
		scanf("%d %d %s", &x, &y,temp);
		int len = strlen(temp);
		addEdge(startVertex, i, 1);
		for (int k = 0; k < len; k++) {
			mmap[y][x + k] = temp[k];
			owner[y][x + k] = i;
		}
		
	}

	for (int i = 0; i < V; i++) {
		scanf("%d %d %s", &x, &y, temp);
		int len = strlen(temp);
		addEdge(i+H, endVertex, 1);
		for (int k = 0; k < len; k++) {
			if (mmap[y + k][x] != 0 && mmap[y + k][x] != temp[k]) {
				addEdge(owner[y + k][x], i + H, 1);
			}
		}
	}
}

int main() {
	scanf("%d", &testcase);
	while (testcase--) {
		input();
		int ans = H + V - executeDinic();
		printf("%d\n", ans);
	}
	return 0;
}