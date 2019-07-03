#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <utility>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
using namespace std;
const int MAX_V = 100000;
const int MAX_E = 500000;
const int MAX_D = 19;
const int MAX = MAX_V * 2;
typedef pair<int, int> Edge;
struct BCCNode {
	bool isArcPoint;
	bool isArcCut;
	vector<int> adj;
	BCCNode() : BCCNode(false) {}
	BCCNode(bool flag) : isArcPoint(flag), isArcCut(false) {}
};
class BlockCutTree {
public:
	int V, E;
	unordered_map<int, int> adj[MAX_V];
	int C;
	int vcNum[MAX_V];
	int ecNum[MAX_E];
	unordered_set<int> ap;
	BCCNode cn[MAX];
	void input() {
		scanf("%d %d", &V, &E);
		for (int i = 0; i < E; ++i) {
			int u, v;
			scanf("%d %d", &u, &v);
			--u; --v;
			adj[u][v] = adj[v][u] = i;
		}
	}
	void construct() {
		C = dcnt = 0;
		fill(dfsn, dfsn + V, -1);
		for (int i = 0; i < V; ++i) {
			if (dfsn[i] < 0) getBCC(i);
			if (adj[i].size() == 1) ap.insert(i);
		}
		for (int u : ap) {
			cn[C] = BCCNode(true);
			for (auto &p : adj[u]) {
				int X = ecNum[p.second];
				cn[C].adj.push_back(X);
				cn[X].adj.push_back(C);
			}
			vcNum[u] = C++;
		}
		memset(cParent, -1, sizeof(cParent));
		fill(cDepth, cDepth + C, -1);
		makeTreeByDFS(0, 0);
		for (int j = 0; j < MAX_D - 1; ++j) {
			for (int i = 0; i < C; ++i)
				if (cParent[i][j] != -1)
					cParent[i][j + 1] = cParent[cParent[i][j]][j];
		}
	}
	bool query1(int u, int v, int a, int b) {
		int e = ecNum[adj[a][b]];
		if (!cn[e].isArcCut) return true;
		u = vcNum[u];
		v = vcNum[v];
		if (u == v) return true;
		int w = getLCA(u, v);
		if (e == w) return false;
		if (getLCA(w, e) == e) return true;
		return (getLCA(u, e) != e && getLCA(v, e) != e);
	}
	bool query2(int u, int v, int a) {
		u = vcNum[u];
		v = vcNum[v];
		a = vcNum[a];
		if (!cn[a].isArcPoint) return true;
		if (u == v) return true;
		int w = getLCA(u, v);
		if (a == w) return false;
		if (getLCA(w, a) == a) return true;
		return (getLCA(u, a) != a && getLCA(v, a) != a);
	}

private:
	stack<Edge> S;
	int dcnt, dfsn[MAX];
	int cParent[MAX][MAX_D];
	int cDepth[MAX];
	int getBCC(int curr, int prev = -1) {
		int result = dfsn[curr] = dcnt++;
		for (auto &p : adj[curr]) {
			int next = p.first;
			if (next == prev) continue;

			if (dfsn[curr] > dfsn[next]) S.push(Edge(curr, next));
			if (dfsn[next] >= 0) result = min(result, dfsn[next]);
			else {
				int temp = getBCC(next, curr);
				result = min(result, temp);
				if (temp >= dfsn[curr]) {
					cn[C] = BCCNode();
					int cnt = 0;
					while (!S.empty()) {
						int u = S.top().first, v = S.top().second;
						S.pop();
						ecNum[adj[u][v]] = C;
						vcNum[u] = vcNum[v] = C;
						++cnt;
						if (curr == u && next == v) break;
					}
					ap.insert(curr);
					if (cnt == 1) cn[C].isArcCut = true;
					++C;
				}
			}
		}
		return result;
	}
	void makeTreeByDFS(int depth, int curr) {
		cDepth[curr] = depth;
		for (int next : cn[curr].adj) {
			if (cDepth[next] >= 0) continue;
			cParent[next][0] = curr;
			makeTreeByDFS(depth + 1, next);
		}
	}
	int getLCA(int u, int v) {
		if (cDepth[u] < cDepth[v]) swap(u, v);
		int diff = cDepth[u] - cDepth[v];

		for (int i = 0; diff > 0; ++i) {
			if (diff % 2) u = cParent[u][i];
			diff /= 2;
		}
		if (u != v) {
			for (int i = MAX_D - 1; i >= 0; --i) {
				if (cParent[u][i] != -1 && cParent[u][i] != cParent[v][i]) {
					u = cParent[u][i];
					v = cParent[v][i];
				}
			}
			u = cParent[u][0];
		}
		return u;
	}
};
BlockCutTree BCT;

int main() {
	BCT.input();
	BCT.construct();
	int Q;
	scanf("%d", &Q);
	for (int i = 0; i < Q; ++i) {
		int o, u, v, a, b;
		bool result;
		scanf("%d %d %d %d", &o, &u, &v, &a);
		if (o == 1) {
			scanf("%d", &b);
			result = BCT.query1(u - 1, v - 1, a - 1, b - 1);
		}
		else result = BCT.query2(u - 1, v - 1, a - 1);
		puts(result ? "yes" : "no");
	}
}
