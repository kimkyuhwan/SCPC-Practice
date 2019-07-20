#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int N, M, K, a, b;
ll c;
int idx = 1;
vector<ll> arr, seg;

ll init(vector<ll> &a, vector<ll> &tree, int node, int start, int end) {
	if (start == end) {
		return tree[node] = arr[start];
	}
	int mid = (start + end) >> 1;
	return tree[node] = init(a, tree, node * 2, start, mid) + init(a, tree, node * 2 + 1, mid + 1, end);
}

void update(vector<ll> &tree, int node, int index, int start, int end, ll diff) {
	if (index < start || index > end) { return; }
	tree[node] += diff;
	if (start != end) {
		int mid = (start + end) >> 1;
		update(tree, node * 2, index, start, mid, diff);
		update(tree, node * 2 + 1, index, mid + 1, end, diff);
	}
}

ll query(vector<ll> &tree, int node, int start, int end, int left, int right) {
	if (left > end || right < start) return 0;
	if (left <= start && end <= right) {
		return tree[node];
	}
	int mid = (start + end) >> 1;
	return query(tree, node*2, start, mid,left,right) + query(tree, node*2+1, mid + 1, end, left, right);
}


int main()
{
	scanf("%d %d %d", &N, &M, &K);
	while (idx < N) { idx <<= 1; }
	arr.resize(idx + 1);
	for (int i = 1; i <= N; i++) scanf("%lld", &arr[i]);
	seg.resize(idx * 2+1);
	init(arr, seg, 1, 1, idx);
	for (int i = M + K; i > 0; i--) {
		scanf("%d %d %lld", &a, &b, &c);
		if (a == 1) {
			ll val = c - seg[idx + b - 1];
			update(seg, 1, b, 1, idx, val);
		} 
		else if (a == 2) {
			printf("%lld\n", query(seg, 1, 1, idx, b, c));
		} 
	}
	return 0;
}