#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
int testcase, ans;
int N, M;
int startVertex, endVertex, numberOfVertex;
char mmap[12][12];
int dy[6] = { -1,0,0,-1,1,1 };
int dx[6] = { -1,-1,1,1,-1,1 };
struct Edge {
	int v, cap, rev;
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
	for (int i = 0; i < edges[here].size(); i++) {
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
			ret += 1;
		}
	}
	return ret;
}

bool isPossiblePosition(int y, int x) {
	return x >= 0 && x < M && y >= 0 && y < N;
}
int getVertexNumber(int y,int x) {
	return y*M + x;
}

void addEdge(int start, int end, int cap) {
	edges[start].emplace_back(end, cap, edges[end].size());
	edges[end].emplace_back(start, cap, edges[start].size()-1);
}

void makeEdges() {
	edges.clear();
	level.clear();
	work.clear();
	edges.resize(numberOfVertex);
	level.resize(numberOfVertex);
	work.resize(numberOfVertex);
}
void input() {
	memset(mmap, 0, sizeof(mmap));
	ans = 0;
	scanf("%d %d", &N, &M);
	startVertex = N*M * 2;
	endVertex = startVertex + 1;
	numberOfVertex = endVertex + 1;
	makeEdges();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf(" %c", &mmap[i][j]);
			if (mmap[i][j] == '.') {
				ans++;
				int curVertex = getVertexNumber(i, j);
				if (j % 2 == 0) {
					addEdge(startVertex, curVertex * 2, 1);
				}
				else {
					addEdge(curVertex * 2 + 1, endVertex, 1);
				}
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (mmap[i][j] == '.') {
				int curVertex = getVertexNumber(i, j);
				for (int k = 0; k < 6; k++) {
					int ny = i + dy[k];
					int nx = j + dx[k];
					if (isPossiblePosition(ny, nx) && mmap[ny][nx] == '.') {
						int nextVertex = getVertexNumber(ny, nx);
						addEdge(curVertex * 2, nextVertex * 2 + 1, 1);
					}

				}
			}
		}
		}
}



int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &testcase);
	while (testcase--) {
		input();
		ans -= executeDinic();
		printf("%d\n", ans);
	}
	return 0;
}