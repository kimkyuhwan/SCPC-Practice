#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
int N, M;
int R, C;
int startVertex, endVertex, numberOfVertex;
struct Edge {
	int v, cap, cost, rev;
	Edge(int _v, int _cap, int _cost, int _rev) : v(_v), cap(_cap), cost(_cost), rev(_rev) {}
};
vector<vector<Edge> > edges;
vector<int> dist, preVertex, preIndex;
vector<bool> inQ;
char mmap[51][51];
int dy[4] = { 0,0,-1,1 };
int dx[4] = { -1,1,0,0 };
int carCnt;
int getVertex(int y, int x) {
	return y*C + x;
}

bool isPossiblePosition(int y, int x) {
	return y >= 0 && y < R && x >= 0 && x < C;
}

bool makeSPFA() {
	fill(dist.begin(), dist.end(), INF);
	fill(preVertex.begin(), preVertex.end(), -1);
	fill(preIndex.begin(), preIndex.end(), -1);
	fill(inQ.begin(), inQ.end(), false);
	queue<int> q;
	q.push(startVertex);
	inQ[startVertex] = true;
	dist[startVertex] = 0;
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		inQ[here] = false;
		for (int i = 0; i < edges[here].size(); i++) {
			int there = edges[here][i].v;
			int thereCap = edges[here][i].cap;
			int thereCost = edges[here][i].cost;

			if (thereCap > 0 && dist[there] > dist[here] + thereCost) {
				dist[there] = dist[here] + thereCost;
				preVertex[there] = here;
				preIndex[there] = i;
				if (!inQ[there]) {
					q.push(there);
					inQ[there];
				}
			}
		}
	}
	return preVertex[endVertex] != -1;
}

int executeMCMF(int val) {
	int maxCost = 0, totalFlow = 0;
	while (makeSPFA()) {
		int flow = INF;
		int hereCost = 0;
		for (int pos = endVertex; pos != startVertex; pos = preVertex[pos]) {
			int pre = preVertex[pos];
			int idx = preIndex[pos];
			flow = min(flow, edges[pre][idx].cap);
		}
		for (int pos = endVertex; pos != startVertex; pos = preVertex[pos]) {
			int pre = preVertex[pos];
			int idx = preIndex[pos];
			edges[pre][idx].cap -= flow;
			edges[pos][edges[pre][idx].rev].cap += flow;
			hereCost += 1;
		}
		totalFlow += flow;
		maxCost = max(maxCost, hereCost);
	}
	if (totalFlow != carCnt) return -1;
	return maxCost;
}

void addEdge(int start, int end, int cap, int cost) {
	edges[start].emplace_back(end, cap, cost, edges[end].size());
	edges[end].emplace_back(start, 0, -cost, edges[start].size()-1);
}

void makeEdges() {
	edges.resize(numberOfVertex);
	dist.resize(numberOfVertex);
	preVertex.resize(numberOfVertex);
	preIndex.resize(numberOfVertex);
	inQ.resize(numberOfVertex);
}

void input() {
	scanf("%d %d", &R, &C);
	startVertex = R*C;
	endVertex = startVertex + 1;
	numberOfVertex = endVertex + 1;
	makeEdges();
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			int curVertex = getVertex(i, j);
			scanf(" %c", &mmap[i][j]);
			if (mmap[i][j] == 'C') {
				addEdge(startVertex, curVertex, 1, 0);
				carCnt++;
			}
			else if (mmap[i][j] == 'P') {
				addEdge(curVertex, endVertex, 1, 0);
			}
		}
	}
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (mmap[i][j] == 'X') {
				continue;
			}
			int curVertex = getVertex(i, j);
			for(int k=0;k<4;k++){
				int ny = i + dy[k];
				int nx = j + dx[k];
				if (isPossiblePosition(ny, nx) && mmap[ny][nx] != 'X') {
					int newVertex = getVertex(ny, nx);
					addEdge(curVertex, newVertex, INF, 1);
				}
			}
		}
	}
}

int main() {
	input();
	int ans = executeMCMF();
	printf("%d\n", ans);
}