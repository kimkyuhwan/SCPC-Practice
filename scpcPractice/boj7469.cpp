#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m;
int idx = 1;
int a, b, c;
vector<vector<ll> > segtree;
ll val;

void update(int node, int l, int r, int id, ll val) {
	if (id < l || id > r || node >= 2*idx) return;
	if (l <= id && id <= r) segtree[node].push_back(val);
	int mid = (l + r) >> 1;
	update(node * 2, l, mid, id, val), update(node * 2 + 1, mid+1, r, id, val);
}

int query(int node, int l, int r, int nodeL, int nodeR, ll val) {
	if (r < nodeL || l > nodeR) return 0;
	if (l <= nodeL && nodeR <= r) return upper_bound(segtree[node].begin(), segtree[node].end(), val) - segtree[node].begin();
	int mid = (nodeL + nodeR) >> 1;
	return query(node * 2, l, r, nodeL, mid, val) + query(node * 2 + 1, l, r, mid + 1, nodeR, val);
}

int main() {
	scanf("%d %d", &n, &m);
	while (idx < n) {
		idx <<= 1;
	}
	segtree.resize(2 * idx + 1);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &val);
		update(1, 1, idx,i, val);
	}
	for (int i = 1; i <= 2 * idx; i++) sort(segtree[i].begin(), segtree[i].end());
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &c);

		int L = -1e9, R = 1e9;
		while (L < R) {
			int mid = (L + R) >> 1;
			if (query(1, a, b, 1, idx, mid) >= c) {
				R = mid;
			}
			else {
				L = mid + 1;
			}
		}
		printf("%d\n", L);
	}
}