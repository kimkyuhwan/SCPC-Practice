#include <bits/stdc++.h>
using namespace std;
const int MAX_VALUE = 100010;
int N, M, X, Y, K, Xn;
int a, b;
int w[MAX_VALUE];
int x[MAX_VALUE];
map<int,int> dx;
int depth[MAX_VALUE];
vector<int> v[MAX_VALUE];
int parent[MAX_VALUE][17];

struct node {
	int c;
	node *left, *right;
	node(int _c, node *a, node *b) : c(_c), left(a), right(b) {}
	node *update(int l, int r, int w);
}*root[MAX_VALUE];
node* node::update(int l, int r, int w) {
	if (l <= w && w <= r) {
		if (l == r) return new node(this->c + 1, NULL, NULL);
		int mid = (l + r) >> 1;
		return new node(this->c + 1, this->left->update(l, mid, w), this->right->update(mid + 1, r, w));
	}
	return this;
}
void dfs(int here, int prev) {
	root[here] = root[prev]->update(1, Xn, w[here]);
	for (int there : v[here]) {
		if (there == prev) continue;
		parent[there][0] = here;
		depth[there] = depth[here] + 1;
		dfs(there, here);
	}
}

int getLCA(int u, int v) {
	if (depth[u] < depth[v]) swap(u, v);
	int diff = depth[u] - depth[v];
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

int query(node *a, node *b, node *c, node *d, int left, int right, int k) {
	if (left == right) return left;
	int cnt = a->left->c + b->left->c - c->left->c - d->left->c;
	int mid = (left + right) >> 1;
	if (cnt >= k) return query(a->left, b->left, c->left, d->left, left, mid, k);
	return query(a->right, b->right, c->right, d->right, mid+1, right, k - cnt);
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &w[i]);
		x[i] = w[i];
	}
	sort(x + 1, x + N + 1);
	Xn = unique(x + 1, x + N + 1) - (x + 1);
	for (int i = 1; i <= Xn; i++) dx[x[i]] = i;
	for (int i = 1; i <= N; i++) w[i] = dx[w[i]];
	for (int i = 1; i < N; i++) {
		scanf("%d %d", &a, &b);
		v[a].push_back(b);
		v[b].push_back(a);
	}
	root[0] = new node(0, NULL, NULL);
	root[0]->left = root[0]->right = root[0];

	dfs(1, 0);
	for (int j = 1; j <= 16; j++) {
		for (int i = 1; i <= N; i++){
			if (parent[i][j - 1] == -1) continue; 
			parent[i][j] = parent[parent[i][j - 1]][j - 1];
		}
	}
	for (int i = 1; i <= M; i++) {
		scanf("%d %d %d", &X, &Y, &K);
		int lca = getLCA(X, Y);
		int res = query(root[X], root[Y], root[lca], root[parent[lca][0]], 1, Xn, K);
		printf("%d\n", x[res]);
	}
}