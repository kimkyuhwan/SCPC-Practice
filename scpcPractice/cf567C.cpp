#include <bits/stdc++.h>
#include <random>
using namespace std;
typedef long long ll;
#define MOD 19683
int n, m;
char mmap[1010][1010];
int datar[1010][1010];
int dy[2] = { 1,0 };
int dx[2] = { 0,1 };

int dfs1(int py, int px, int cnt, int dir) {
	int ret = 0;
	if (cnt == 3) {ret = 1;}
	if (py == n - 1 && dir == 0) return ret;
	if (px == m - 1 && dir == 1) return ret;
	int ny = py + dy[dir];
	int nx = px + dx[dir];

	if (dir == 0) {
		if (mmap[py][px] != mmap[ny][nx]) {
			int ncnt = min(3, cnt + 1);
			ret += dfs1(ny, nx, ncnt, 0);
			if (ncnt == 3) {
				ret += dfs1(py, px+1, 1, 1);
			}
		}
		else {
			int ncnt = 1;
			ret += dfs1(ny, nx, ncnt, 0);
		}
	}
	else if (dir == 1) {
		if (datar[py][px] != datar[ny][nx]) {
			ret += dfs1(py, px + 1, cnt, 0);
			int ncnt = cnt + 1;
			ret += dfs1(ny, nx, ncnt, 1);
			if (ncnt == 3) {
				ret += dfs1(ny, nx, 1, 1) + cnt;
			}
		}
		else {
			int ncnt = 1;
			ret += dfs1(ny, nx, ncnt, 0);
		}
	}
	return ret;
}


int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf(" %c", &mmap[i][j]);
		}
	}

	for (int i = 0; i < m; i++) {
		int val = 0;
		for (int j = 0; j < n; j++) {
			val *= 27;
			val += (mmap[j][i] - 'a');
			val %= MOD;
			datar[j][i] = val;
		}
	}
	int ans = dfs1(0, 0, 1, 0);
	printf("%d\n", ans);
}