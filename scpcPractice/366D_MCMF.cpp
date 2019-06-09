#include <bits/stdc++.h>
using namespace std;
#define INF 1e18
typedef long long ll;
struct Edge {
	int v, cost, rev;
	ll cap;
	Edge(int _v, ll _cap, int _cost, int _rev) : v(_v), cap(_cap), cost(_cost), rev(_rev) {}
};

vector<vector<Edge> > edges;
vector<int> isFinish;
vector<ll> dist;
vector<int> preVertex, preIndex;
vector<bool> inQ;
vector<int> ans;
vector< pair<int, int> > used;
map<int, vector<int> > xx, yy;
map<pair<int, int>, int> querys;
int n, m, x, y;
int r, b;
int t, l;
int d[100010];
int vertexCnt[100010];
int startVertex, endVertex, numberOfVertex;
int finishCnt;
bool isNotPossible;

bool canFinish(pair<int, int> src, int idx) {
	return (abs(src.first - src.second) <= d[idx]);
}

void checkFinish(pair<int,int> src,int idx) {
	if (canFinish(src,idx)) {
		isFinish[idx] = true;
		finishCnt++;
	}
}



bool makeSPFA() {
	queue<int> q;
	fill(dist.begin(), dist.end(), INF);
	fill(preVertex.begin(), preVertex.end(), -1);
	fill(preIndex.begin(), preIndex.end(), -1);
	fill(inQ.begin(), inQ.end(), false);
	dist[startVertex] = 0;
	q.push(startVertex);
	inQ[startVertex] = true;
	while (!q.empty()) {
		int here = q.front(); q.pop();
		inQ[here] = false;
		for (int i = 0; i < edges[here].size(); i++) {
			int there = edges[here][i].v;
			ll thereCap = edges[here][i].cap;
			int thereCost = edges[here][i].cost;
			if (there > n && there <= n + m && isFinish[there-n]) {
				continue;
			}
			if (thereCap > 0 && dist[there] > dist[here] + thereCost) {
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

void executeMCMF() {
	ll totalFlow = 0, cost = 0;
	int def = (r < b) ? 0 : 1;
	used.resize(querys.size()+1);
	ans.resize(n, def);
	while (makeSPFA()) {
 		ll flow = INF;
		for (int pos = endVertex; pos != startVertex; pos = preVertex[pos]) {
			int pre = preVertex[pos];
			int idx = preIndex[pos];
			flow = min(flow, edges[pre][idx].cap);
		}

		for (int pos = endVertex; pos != startVertex; pos = preVertex[pos]) {
			int pre = preVertex[pos];
			int idx = preIndex[pos];
			cost += flow * edges[pre][idx].cost;
			if (edges[pre][idx].cost == -1) {
				used[pos - n].first++;
				vertexCnt[pos - n]--;
				if (vertexCnt[pos - n] <= 0) {
					checkFinish(used[pos - n], pos - n);
				}
			}
			else if (edges[pre][idx].cost == 1) {
				used[pos - n].first--;
				used[pos - n].second++;
				ans[pre - 1] = 1- ans[pre-1];
				vertexCnt[pos - n]--;
				if (vertexCnt[pos - n] <= 0) {
					checkFinish(used[pos - n], pos - n);
				}
			}
			edges[pre][idx].cap -= flow;
			edges[pos][edges[pre][idx].rev].cap += flow;
		}
		totalFlow += flow;
	}
	if (finishCnt != querys.size()) {
		isNotPossible = true;
	}
}

void addEdge(int start, int end, ll cap, int cost) {
	edges[start].emplace_back(end, cap, cost, edges[end].size());
	edges[end].emplace_back(start, 0, -cost, edges[start].size() - 1);
}

void makeEdges() {
	edges.resize(numberOfVertex);
	dist.resize(numberOfVertex);
	preVertex.resize(numberOfVertex);
	preIndex.resize(numberOfVertex);
	inQ.resize(numberOfVertex);
	isFinish.resize(m + 1);
}

void input() {
	scanf("%d %d", &n, &m);
	scanf("%d %d", &r, &b);
	startVertex = 0;
	endVertex = n+m+1;
	numberOfVertex = endVertex + 1;
	makeEdges();
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &x, &y);
		xx[x].push_back(i);
		yy[y].push_back(i);
		addEdge(startVertex, i,INF, 0);
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", &t, &l, &d[i]);
		if (querys.count({ t,l })) {
			querys[{t, l}] = min(querys[{t, l}], d[i]);
		}
		else {
			querys[{t, l}] = d[i];
		}
	}
	int i = 1;
	for (auto it = querys.begin(); it != querys.end(); it++,i++) {
		t = it->first.first;
		l = it->first.second;
		int dd = it->second;
		d[i] = dd;
		if (t == 1) {
			for (int j = 0; j < xx[l].size(); j++) {
				int here = xx[l][j];
				int minn = min(r, b);
				int maxx = max(r, b);
				addEdge(here, n + i, minn, -1);
				addEdge(here, n + i, maxx - minn, 1);
			}
			vertexCnt[i] = xx[l].size();

		}
		else {
			for (int j = 0; j < yy[l].size(); j++) {
				int here = yy[l][j];
				int minn = min(r, b);
				int maxx = max(r, b);
				addEdge(here, n + i, minn, -1);
				addEdge(here, n + i, maxx - minn, 1);
			}
			vertexCnt[i] = xx[l].size();
		}
		addEdge(n + i, endVertex, INF, 0);
	}
}
int main() {
	input();
	executeMCMF();
	if (isNotPossible) {
		puts("-1");
	}
	else {
		ll sol = 0;
		for (int i = 0; i < ans.size(); i++) {
			sol += ans[i] == 0 ? r : b;
		}
		printf("%lld\n", sol);
		for (int i = 0; i < ans.size(); i++) {
			printf("%c", ans[i]==0 ? 'r' : 'b');
		}
	}
}