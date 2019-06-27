#include <bits/stdc++.h>
using namespace std;
int n, m, cnt, ansCnt;
char mmap[1010][1010];
bool visited[1010][1010];
int ans[1010][1010];
int dx[4] = { 0,1,0,-1 };
int dy[4] = { -1,0,1,0 };
int maxx[1010][1010];
bool isPossiblePosition(int y, int x) {
	return y >= 0 && y < n && x >= 0 && x < m;
}


int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf(" %c", &mmap[i][j]);
			if (mmap[i][j] == '*') cnt++;
		}
	}
	for (int i = 1; i < n-1; i++) {
		for (int j = 1; j < m-1; j++) {
			bool isPossible = true;
			if (mmap[i][j] != '*') continue;
			
			for (int c = 1;; c++) {
				if (c == 2) {
					if (!visited[i][j]) {
						visited[i][j] = true;
						cnt--;
					}
					ansCnt++;
				}
				for (int k = 0; k < 4; k++) {
					int y = i + dy[k] * c;
					int x = j + dx[k] * c;
					if (!isPossiblePosition(y, x)) {
						isPossible = false;
						break;
					}
					if (mmap[y][x] != '*') {
						isPossible = false;
						break;
					}
				}
				if (!isPossible)  break;
				for (int k = 0; k < 4; k++) {
					int y = i + dy[k] * c;
					int x = j + dx[k] * c;
					if (!visited[y][x]) {
						visited[y][x] = true;
						cnt--;
					}
				}
				ans[i + 1][j + 1] = c;
			}
		}
	}
	if (cnt != 0) {
		puts("-1");
		return 0;
	}
	printf("%d\n", ansCnt);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (ans[i][j] != 0) {
				printf("%d %d %d\n", i, j, ans[i][j]);
			}
		}
	}
}