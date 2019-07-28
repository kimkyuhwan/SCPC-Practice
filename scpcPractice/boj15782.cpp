#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100007;
int N, M, cmd;
int a, b, idx=1;
vector<vector<int> > edges;
int val[MAXN];
int numChild[MAXN];
int numbering[MAXN];
int rnumbering[MAXN];
int num;
vector<int> seg, lazy;
int dfs(int here, int par = 0) {
	numChild[here] = 0;
	for (int there : edges[here]) {
		if (there == par) continue;
		numChild[here] += dfs(there, here)+1;
	}
	numbering[here] = ++num;
	rnumbering[num] = here;
	return numChild[here];
}

int init(int node, int left, int right) {
	if (left == right) {
		return seg[node] = val[rnumbering[left]];
	}
	int mid = (left + right) >> 1;
	return seg[node] = init(node * 2, left, mid) ^ init(node * 2 + 1, mid + 1, right);
}

void lazyUpdate(int node, int left, int right) {
	if (lazy[node]) {
		int sz = (right - left + 1);
		if (sz % 2 == 1) {
			seg[node] ^= lazy[node];
		}
		if (left != right) {
			lazy[node * 2] ^= lazy[node];
			lazy[node * 2+1] ^= lazy[node];
		}
		lazy[node] = 0;
	}
}

int query(int node, int left, int right, int start, int end) {
	lazyUpdate(node, left, right);
	if (left > end || right < start) return 0;
	if (start <= left && right <= end) {
		return seg[node];
	}
	int mid = (left + right) >> 1;
	return query(node * 2, left, mid, start, end) ^ query(node * 2+1, mid + 1, right, start, end);
}


void update(int node,int val, int left, int right, int start, int end) {
	lazyUpdate(node, left, right);
	if (left > end || right < start) return;
	if (start <= left && right <= end) {
		int sz = (right - left + 1);
		if (sz % 2 == 1) {
			seg[node] ^= val;
		}
		if (left != right) {
			lazy[node * 2] ^= val;
			lazy[node * 2 + 1] ^= val;
		}
		return;
	}
	int mid = (left + right) >> 1;
	update(node * 2, val, left, mid, start, end);
	update(node * 2 + 1, val, mid + 1, right, start, end);
	seg[node]=seg[node*2]^seg[node*2+1];
}

int main()
{
	scanf("%d %d", &N, &M);
	edges.resize(N + 1);
	while (idx < N) {
		idx <<= 1;
	}
	lazy.resize(idx*2);
	seg.resize(idx * 2);
	for (int i = 1; i < N; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	for (int i = 1; i <= N; i++) scanf("%d", &val[i]);
	dfs(1);
	init(1, 1, idx);
	for (int i = 0; i < M; i++) {
		scanf("%d", &cmd);
		if (cmd == 1) {
			scanf("%d", &a);
			int ans = query(1, 1, idx, numbering[a] - numChild[a], numbering[a]);
			printf("%d\n", ans);
		}
		else if (cmd == 2) {
			scanf("%d %d", &a,&b);
			update(1, b, 1, idx, numbering[a] - numChild[a], numbering[a]);
		}
	}
}