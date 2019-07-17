#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int q, n, m;
int cnt;
vector<vector<char> > mmap;
vector<int> xx, yy;
int main() {
	scanf("%d", &q);
	for (int i = 0; i < q; i++) {
		scanf("%d %d", &n, &m);
		mmap.assign(n, vector<char>(m));
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < m; k++) {
				scanf(" %c", &mmap[j][k]);
			}
		}
		xx.assign(n,0);
		for (int j = 0; j < n; j++) {
			cnt = 0;
			for (int k = 0; k < m; k++) {
				if (mmap[j][k] == '*') cnt++;
			}
			xx[j] = cnt;
		}
		yy.assign(m,0);
		for (int k = 0; k < m; k++) {
			cnt = 0;
			for (int j = 0; j < n; j++) {
				if (mmap[j][k] == '*') cnt++;
			}
			yy[k] = cnt;
		}
		int ans = 10000000;
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < m; k++) {
				int val = n + m - xx[j] - yy[k];
				if (mmap[j][k] != '*') {
					val--;
				}
				ans = min(ans, val);
			}
		}
		printf("%d\n", ans);
	}
}