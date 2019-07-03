#include <bits/stdc++.h>
using namespace std;
int n, k, val;
int parent[610];
int child[610];

int main() {
	memset(parent, -1, sizeof(parent));
	scanf("%d %d", &n, &k);
	for (int i = 0; i <= 256; i++) {
		parent[i] = i;
		child[i] = i;
	}
	for (int i = 0; i < n; i++) {
		scanf("%d", &val);
		int m = val + 1 - k;
		m = max(0, m);
		if (child[val] != val) {
			printf("%d ", parent[val]);
			continue;
		}
		while(parent[m] < m && m<val) {
			m++;
		}
		for (int i = m; i <= val; i++) {
			parent[i] = m;
			child[i] = val;
		}
		printf("%d ", parent[val]);

	}
}