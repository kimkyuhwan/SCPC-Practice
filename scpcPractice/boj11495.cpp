#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
int T;
int dy[2] = {0,1};
int dx[2] = {1,0};
struct Edge {
	int v, cap, rev;
	Edge(int _v, int _cap, int _rev) : v(_v), cap(_cap), rev(_rev) {}
};

vector<vector<Edge> > edges;
vector<int> level, work;
int startVertex, endVertex, numberOfVertex;
int n, m;
int w[3010];
int rb[3010];
bool isPossbilePostion(int y, int x) {
	return y >= 0 && y < n && x >= 0 && x < m;
}

int getVertex(int y, int x) {
	return y*m + x;
}


bool makeLevelGraph() {
	queue<int> q;
	fill(level.begin(), level.end(), -1);
	q.push(startVertex);
	level[startVertex]=0;
	while (!q.empty()) {
		int here = q.front(); q.pop();
		for (int i = 0; i < edges[here].size();i++) {
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
		if (thereCap > 0 && level[here] + 1 == level[there]) {
			int cap = dfs(there, min(currentCap,thereCap));
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
	int totalFlow = 0, cost = 0;
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

void makeEdges() {
	edges.assign(numberOfVertex,vector<Edge>());
	work.assign(numberOfVertex,0);
	level.assign(numberOfVertex,-1);
}


void addEdge(int start, int end, int cap) {
	edges[start].emplace_back(end, cap,  edges[end].size());
	edges[end].emplace_back(start, 0,edges[start].size() - 1);
}
int sum;
void input() {
	int num;
	scanf("%d %d", &n, &m);
	startVertex = n*m;
	endVertex = startVertex + 1;
	numberOfVertex = endVertex + 1;
	makeEdges();
	int cnt = 0;
	sum = 0;
	for (int i = 0; i < n; i++) {
		int flag = i%2;
		for (int j = 0; j < m; j++) {
			scanf("%d", &w[cnt]);
			if (flag % 2 == 0) {
				rb[cnt] = 0;
				addEdge(startVertex, cnt, w[cnt]);
			}
			else if (flag % 2 == 1) {
				rb[cnt] = 1;
				addEdge(cnt, endVertex, w[cnt]);
			}
			sum += w[cnt];
			cnt++;
			flag++;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int currentVertex = getVertex(i, j);
			for (int k = 0; k < 2; k++) {
				int ny = i + dy[k];
				int nx = j + dx[k];
				if (isPossbilePostion(ny, nx)) {
					int nextVertex = getVertex(ny, nx);
					if (rb[currentVertex] == 0) {
						addEdge(currentVertex, nextVertex, INF);
					}
					else {
						addEdge(nextVertex, currentVertex, INF);
					}
				}
			}
		}
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		input();
		int ans = executeDinic();
		printf("%d\n", sum-ans);
	}
}