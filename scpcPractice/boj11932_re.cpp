#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100007;
const int MAX_DEPTH = 17;
const int MAX_ST = 1 << MAX_DEPTH;
const int MAX_NODE = MAX_ST + MAXN * MAX_DEPTH;
int N, M, a, b;
int X, Y, K;
map<int, int> dx;
int w[MAXN], x[MAXN], Xn;
int depth[MAXN], parent[MAXN][MAX_DEPTH];
vector<vector<int> > edges;

struct Node {
	int val;
	int left, right;
	int currentNum, lNum, rNum;
	Node() : Node(-1, -1, -1) {}
	Node(int left, int right, int num) : val(0), left(left), right(right), currentNum(num), lNum(-1), rNum(-1) {}
};

struct PST {
	int Tn;
	int nodeCnt;
	int root[MAXN];
	Node node[MAX_NODE];
	PST() : Tn(0), nodeCnt(0) {
		
	}

	void init() {
		fill(root, root + MAXN, -1);
		root[0] = initialize(1, Xn);
		node[0].lNum = 0, node[0].rNum = 0;
		dfs(1, 0);
	}

	int initialize(int left, int right) {
		Node &curr = node[nodeCnt] = Node(left, right, nodeCnt);
		nodeCnt++;
		if (left < right) {
			int mid = (left + right) >> 1;
			curr.lNum = initialize(left, mid);
			curr.rNum = initialize(mid + 1, right);
		}
		return curr.currentNum;
	}
	
	int addNode(Node &shadow, int x, int left, int right) {
		if (right < x && left > x) return shadow.currentNum;
		Node &curr = node[nodeCnt] = Node(left, right, nodeCnt);
		nodeCnt++;
		if (left == right) {
			curr.val = shadow.val + 1;
		}
		else {
			int mid = (left + right) >> 1;
			curr.lNum = addNode(node[shadow.lNum], x,left, mid);
			curr.rNum = addNode(node[shadow.rNum], x, mid+1, right);
			curr.val = node[curr.lNum].val+node[curr.rNum].val;
		}
		return curr.currentNum;
	}

	void dfs(int here, int par) {
		root[here] = addNode(node[root[par]], w[here], 1, Xn);
		for (int there : edges[here]) {
			if (there == par) continue;
			depth[there] = depth[here] + 1;
			parent[there][0] = here;
			dfs(there, here);
		}
	}

	int query(Node &a, Node &b, Node &c, Node &d, int left, int right, int K) {
		if (left == right) return left;
		int cnt = node[a.lNum].val + node[b.lNum].val - node[c.lNum].val - node[d.lNum].val;
		int mid = (left + right) >> 1;
		if (cnt >= K) return query(a.lNum, b.lNum, c.lNum, d.lNum , left, mid, K);
		return query(a.rNum, b.rNum, c.rNum, d.rNum, mid + 1, right, K - cnt);

	}

	int queryStart(int a, int b, int c, int d, int left, int right, int K) {
		return query(root[a], root[b], root[c], root[d], left, right, K);
	}

	int query(int a, int b, int c, int d, int left, int right, int K) {
		return query(node[a], node[b], node[c], node[d], left, right, K);
	}
}pst;

int getLCA(int u, int v) {
	if (depth[u] < depth[v]) swap(u, v);
	for (int i = 16; i >= 0; i--) {
		if ((1 << i) <= depth[u] - depth[v])
			u = parent[u][i];
	}
	if (u == v) return u;
	for (int i = 16; i >= 0; i--)
		if (parent[u][i] != parent[v][i]) {
			u = parent[u][i], v = parent[v][i];
		}
	return parent[v][0];
}


int main() {
	scanf("%d %d", &N, &M);
	
	for (int i = 1; i <= N; i++) {
		scanf("%d", &w[i]);
		x[i] = w[i];
	}
	sort(x + 1, x + N + 1);
	Xn = unique(x + 1, x + N + 1) - (x + 1);
	edges.resize(N + 1);
	for (int i = 1; i <= Xn; i++) {
		dx[x[i]] = i;
	}
	for (int i = 1; i <= N; i++) {
		w[i] = dx[w[i]];
	}
	for (int i = 1; i < N; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	pst.init();
	for (int i = 1; i <= 16; i++) {
		for (int j = 1; j <= N; j++) {
			parent[j][i] = parent[parent[j][i - 1]][i - 1];
		}
	}
	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &X, &Y, &K);
		int lca = getLCA(X, Y);
		int res = pst.queryStart(X, Y, lca, parent[lca][0],1,Xn, K);
		printf("%d\n", x[res]);
	}
}