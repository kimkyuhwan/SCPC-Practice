#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int N, M, K, a, b, c, idx = 1;
ll d;
vector<ll> arr, seg, lazy;

ll init(vector<ll> &a, vector<ll> &tree, int node, int start, int end) {
	if (start == end) {
		return tree[node] = arr[start];
	}
	int mid = (start + end) >> 1;
	return tree[node]=init(a, tree, node * 2, start, mid) + init(a, tree, node * 2 + 1, mid + 1, end);
}

void update_lazy(vector<ll> &tree, vector<ll> &lazy, int node, int start, int end) {
	if (lazy[node] != 0) {
		tree[node] += (end - start + 1)*lazy[node];
		if (start != end) {
			lazy[node * 2] += lazy[node];
			lazy[node * 2 + 1] += lazy[node];
		}
		lazy[node] = 0;
	}
}

void update(vector<ll> &tree, vector<ll> &lazy, int node, int left, int right, int start, int end, ll diff) {
	update_lazy(tree, lazy, node, start, end);
	if (left > end || right < start) return;
	if (left<=start && end <=right) {
		tree[node] += (end-start+1) * diff;
		if (start != end) {
			lazy[node * 2] += diff;
			lazy[node * 2 + 1] += diff;
		}
		return;
	}
	int mid = (start + end) >> 1;
	update(tree, lazy, node * 2, left, right, start, mid, diff);
	update(tree, lazy, node * 2 + 1, left, right, mid+1, end, diff);
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll query(vector<ll> &tree, vector<ll> &lazy, int node, int left, int right, int start, int end) {
	update_lazy(tree, lazy, node, start, end);
	if (left > end || right < start) return 0;
	if (left <= start && end <= right) return tree[node];
	int mid = (start + end) >> 1;
	return query(tree, lazy, node * 2, left, right, start, mid) + query(tree, lazy, node * 2 + 1, left, right, mid + 1, end);
}

int main() {
	scanf("%d %d %d", &N, &M, &K);
	while (idx < N) idx <<= 1;
	arr.resize(idx + 1);
	seg.resize(idx * 2);
	lazy.resize(idx * 2);
	for (int i = 1; i <= N; i++) {
		scanf("%lld", &arr[i]);
	}
	init(arr, seg, 1, 1, idx);
	for (int i = M + K; i > 0; i--) {
		scanf("%d %d %d", &a, &b, &c);
		if (a == 1) {
			scanf("%lld", &d);
			update(seg,lazy,1,b,c,1,idx,d);
		}
		else if(a==2){
			printf("%lld\n", query(seg,lazy,1,b,c,1,idx));
		}
	}
}