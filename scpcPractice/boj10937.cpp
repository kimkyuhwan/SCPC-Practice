#include <bits/stdc++.h>
using namespace std;
#define INF 1e9

struct Edge {
	int v, cap, cost, rev;
	Edge(int _v, int _cap, int _cost, int _rev) : v(_v), cap(_cap),cost(_cost), rev(_rev) {}
};

vector<vector<Edge> > edges;
vector<int> dist, preVertex, preIndex;
vector<bool> inQ;
int startVertex, endVertex, numberOfVertex;
int N;
char mmap[20][20];
int rb[20][20];
int dy[2] = { 0,1 };
int dx[2] = { 1,0 };
int score[3][3] = {
	{100,70,40},
	{70,50,30},
	{40,30,20}
};
bool isPossiblePosition(int y, int x) {
	return y >= 0 && y < N && x >= 0 && x < N;
}

int getVertex(int y, int x) {
	return y*N + x;
}

int getScore(int y, int x, int ny, int nx) {
	int A = mmap[y][x] - 'A';
	int B = mmap[ny][nx] - 'A';
	if (A >= 3 || B>=3) {
		return 0;
	}
	return score[A][B];
}

bool makeLevelGraph() {
	queue<int> q;
	fill(dist.begin(), dist.end(), -INF);
	fill(preVertex.begin(), preVertex.end(), -1);
	fill(preIndex.begin(), preIndex.end(), -1);
	fill(inQ.begin(), inQ.end(), false);
	q.push(startVertex);
	dist[startVertex] = 0;
	inQ[startVertex] = true;
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		inQ[here] = false;
		for (int i = 0; i<edges[here].size();i++) {
			int there = edges[here][i].v;
			int thereCap = edges[here][i].cap;
			int thereCost = edges[here][i].cost;
			if (thereCap > 0 && dist[there] < dist[here] + thereCost) {
				dist[there] = dist[here] + thereCost;
				preVertex[there] = here;
				preIndex[there] = i;
				if (!inQ[there]) {
					q.push(there);
					inQ[there] = true;
				}
			}
		}
	}
	return preVertex[endVertex] != -1;
}
int executeDinic() {
	int cost = 0;
	while (makeLevelGraph()) {
		int flow = INF;
		for (int pos = endVertex; pos != startVertex; pos = preVertex[pos]) {
			int pre = preVertex[pos];
			int idx = preIndex[pos];
			flow = min(flow, edges[pre][idx].cap);
		}
		for (int pos = endVertex; pos != startVertex; pos = preVertex[pos]) {
			int pre = preVertex[pos];
			int idx = preIndex[pos];
			cost += edges[pre][idx].cost*flow;
			edges[pre][idx].cap -= flow;
			edges[pos][edges[pre][idx].rev].cap += flow;
		}
	}
	return cost;
}


void addEdge(int start, int end, int cost, int cap) {
	edges[start].emplace_back(end, cap, cost, edges[end].size());
	edges[end].emplace_back(start, 0,-cost, edges[start].size()-1);
}

void makeEdges() {
	edges.resize(numberOfVertex);
	dist.resize(numberOfVertex);
	preVertex.resize(numberOfVertex);
	preIndex.resize(numberOfVertex);
	inQ.resize(numberOfVertex);
}

void input() {
	scanf("%d", &N);

	startVertex = N*N;
	endVertex = startVertex + 1;
	numberOfVertex = endVertex + 1;
	makeEdges();
	for (int i = 0; i < N; i++) {
		int flag = i % 2;
		for (int j = 0; j < N; j++) {
			scanf(" %c", &mmap[i][j]);
			int currentVertex = getVertex(i, j);
			if (flag % 2 == 0) {
				rb[i][j] = 0;
				addEdge(startVertex, currentVertex, 0,1);
			}
			else {
				rb[i][j] = 1;
			}
			addEdge(currentVertex, endVertex, 0, 1);
			flag++;
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int currentVertex = getVertex(i, j);
			for (int k = 0; k < 2; k++) {
				int ny = i + dy[k];
				int nx = j + dx[k];
				if (isPossiblePosition(ny, nx)) {
					int nextVertex = getVertex(ny, nx);
					if (rb[i][j] == 0) {
						addEdge(currentVertex, nextVertex, getScore(i, j, ny, nx),1);
					}
					else {
						addEdge(nextVertex, currentVertex, getScore(i, j, ny, nx),1);
					}

				}

			}


		}
	}

}

int main() {
	input();
	int ans = executeDinic();
	printf("%d\n", ans);
	return 0;
}