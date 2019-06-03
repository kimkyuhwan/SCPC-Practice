#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
struct Edge {
	int v, cap, rev;
	Edge(int _v, int _cap, int _rev) : v(_v),cap(_cap),rev(_rev) {}
};

vector<vector<Edge> > edges;
vector<int> level, work;

int N, M;
int startVertex, endVertex, numberOfVertex;
char mmap[110][110];
int dy[4] = { 0,1,0,-1 };
int dx[4] = { 1,0,-1,0 };

bool isPossiblePosition(int y, int x) {
	return (x >= 0 && x < M) && (y >= 0 && y < N);
}

int getVertexNum(int y, int x) {
	return y*M + x;
}

bool makeLevelGraph() {
	queue<int> q;
	fill(level.begin(), level.end(), -1);
	q.push(startVertex);
	level[startVertex] = 0;
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

int executeMCMF() {
	int totalFlow = 0;
	int cost = 0;
	while (makeLevelGraph())
	{
		fill(work.begin(), work.end(), 0);
		while (1) {
			int flow = dfs(startVertex,1);
			if (!flow) break;
			totalFlow += flow;
		}
	}
	return totalFlow;
}


void addEdge(int start, int end, int cap, int cost) {
	edges[start].emplace_back(end, cap, edges[end].size());
	edges[end].emplace_back(start, 0, edges[start].size()-1);
}

void makeEdges() {
	edges.resize(numberOfVertex);
	work.resize(numberOfVertex);
	level.resize(numberOfVertex);
}

int input() {
	char C;
	scanf("%d %d", &N, &M);
	numberOfVertex = (N*M * 2 + 1);
	makeEdges();
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			scanf(" %c", &mmap[i][j]);
	for (int i = 0; i < N; i++){
		for (int j = 0; j < M; j++){
			C = mmap[i][j];
			if (C != '#') {
				int currentVertex = getVertexNum(i, j);
				addEdge(currentVertex * 2, currentVertex * 2 + 1, 1, 0);
				if (C == 'K') {
					startVertex = currentVertex *2+ 1;
					for (int k = 0; k < 4; k++) {
						int ny = i + dy[k];
						int nx = j + dx[k];
						if (isPossiblePosition(ny, nx) && mmap[ny][nx]=='H') {
							puts("-1");
							return -1;
						}
					}
				}
				else if (C == 'H') {
					endVertex = currentVertex * 2;
				}
			}
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			int currentVertex = getVertexNum(i, j);
			for (int k = 0; k < 4; k++) {
				int ny = i + dy[k];
				int nx = j + dx[k];
				if (isPossiblePosition(ny, nx) && mmap[ny][nx]!='#') {
					int movedVertex = getVertexNum(ny, nx);
					addEdge(currentVertex * 2 + 1, movedVertex * 2, INF, 0);
				}
			}
		}
	}
	return 0;	
}

int main() {
	int inp = input();
	if (inp == -1) {
		return 0;
	}
	int ans = executeMCMF();
	printf("%d\n", ans);
}