#include <bits/stdc++.h>
using namespace std;
int N, M, idx=1, A;
vector<vector<int> > seg;
vector<int> arr;
int a, b, k;

void update(int node, int left, int right) {
	if (left == right) {
		seg[node].push_back(arr[left]);
		return;
	}
	int l = node * 2;
	int r = node * 2 + 1;
	int mid = (left + right) >> 1;
	update(l, left, mid);
	update(r, mid + 1, right);
	seg[node].resize(seg[l].size() + seg[r].size());
	merge(seg[l].begin(), seg[l].end(), seg[r].begin(), seg[r].end(), seg[node].begin());
}

int query(int node, int left, int right, int start, int end, int val) {
	if (left > end || right < start) return 0;
	if (start <= left && right <= end) {
		int sz = (right - left + 1);
		return sz - (upper_bound(seg[node].begin(), seg[node].end(), val) - seg[node].begin());
	}
	int mid = (left + right) >> 1;
	return query(node * 2, left, mid, start, end, val) + query(node * 2 + 1, mid + 1, right, start, end, val);
}

int main() {
	scanf("%d", &N);
	while (idx < N) {
		idx <<= 1;
	}
	seg.resize(idx * 2);
	arr.resize(idx + 1);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &arr[i]);
	}
	update(1, 1, idx);
	for (int i = 1; i < seg.size(); i++) sort(seg[i].begin(), seg[i].end());
	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &a, &b, &k);
		int ans = query(1, 1, idx, a, b, k);
		printf("%d\n", ans);
	}
}