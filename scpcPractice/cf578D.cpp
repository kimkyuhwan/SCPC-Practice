#include <bits/stdc++.h>
using namespace std;
int n, k, sol;
int mmap[2010][2010];
int testMap[2010][2010];
int psum[2010][2010];
int numOfBlack[2010];
pair<int, int> LR[2010];
char WB;

void init() {
	memset(psum, 0, sizeof(psum));
	memset(numOfBlack, 0, sizeof(numOfBlack));
	memset(LR, 0, sizeof(LR));
}
int getSolution(pair<int,int> cur) {
	int y = cur.first;
	int x = cur.second;
	int ret = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			testMap[i][j] = mmap[i][j];
		}
	}

	for (int i = y, cnt = 0; i <= n && cnt < k; i++, cnt++) {
		for (int j = x, cnt = 0; j <= n && cnt < k; j++, cnt++) {
			testMap[i][j] = 0;
		}
	}

	for (int i = 1; i <= n; i++) {
		bool isExistBlack = false;
		for (int j = 1; j <= n; j++) {
			if (testMap[i][j]) {
				isExistBlack = true;
				break;
			}
		}
		if (!isExistBlack) ret++;
	}
	for (int i = 1; i <= n; i++) {
		bool isExistBlack = false;
		for (int j = 1; j <= n; j++) {
			if (testMap[j][i]) {
				isExistBlack = true;
				break;
			}
		}
		if (!isExistBlack) ret++;
	}
	return ret;
}

pair<int, int> solutionHorizon() {
	int ry=1, rx=1;
	init();
	for (int i = 1; i <= n; i++) {
		int f = -1, b = -1;
		for (int j = 1; j <= n; j++) {
			if (mmap[i][j] == 1) {
				if (f == -1) {
					f = j;
					b = j;
				}
				else {
					b = j;
				}
				psum[i][j] = psum[i][j - 1] + 1;
				numOfBlack[i]++;
			}
		}
		if (f + k <= b) {
			LR[i] = { -1,-1 };
		}
		else {
			int length = (b - f) + 1;
			LR[i] = { f - (k - length), f };
		}
	}
	int ccnt = 0;
	for (int i = 1; i <= n; i++) {
		int cnt = 1;
		if (LR[i].first == -1) continue;
		int L = LR[i].first, R = LR[i].second;
		for (int j = 1; j < k; j++) {
			int nL = LR[i + j].first, nR = LR[i + j].second;
			if ((L <= nL && nL <= R) || (L <= nR && nR <= R)) {
				cnt++;
				L = max(L, nL);
				R = min(R, nR);
			}
		}
		if (ccnt < cnt) {
			rx = L;
			ry = min(n - k + 1, i);
			ccnt = cnt;
		}
	}
	ry = max(1, ry);
	rx = max(1, rx);
	return{ ry,rx };
}

void solutionVertical() {
	for (int j = 1; j <= n; j++) {
		int f = -1, b = -1;
		for (int i = 1; i<= n; i++) {
			
			if (mmap[i][j] == 1) {
				if (f == -1) {
					f = i;
					b = i;
				}
				else {
					b = i;
				}
				psum[i][j] = psum[i-1][j] + 1;
			}
		}
		if (f + k <= b) {
			LR[j] = { -1,-1 };
		}
		else {
			int length = (b - f) + 1;
			LR[j] = { f- (k - length), f };
		}
	}
}

pair<int, int> solution() {
	int ry = 1, rx = 1;
	init();

	int ccnt = 0;
	for (int i = 1; i <= n; i++) {
		int cnt = 1;
		if (LR[i].first == -1) continue;
		int L = LR[i].first, R = LR[i].second;
		for (int j = 1; j < k; j++) {
			int nL = LR[i + j].first, nR = LR[i + j].second;
			if ((L <= nL && nL <= R) || (L <= nR && nR <= R)) {
				cnt++;
				L = max(L, nL);
				R = min(R, nR);
			}
		}
		if (ccnt < cnt) {
			rx = min(n - k + 1, i);
			ry = L;
			ccnt = cnt;
		}
	}
	ry = max(1, ry);
	rx = max(1, rx);
	return{ ry,rx };
}
int main() {
//		freopen("input.txt", "r", stdin);
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf(" %c", &WB);
			if (WB == 'B') mmap[i][j] = 1;
		}
	}
	int ans = 0;
	if (n == k) ans = n*n;
	else {
		ans = max(getSolution(solutionHorizon()), getSolution(solutionVertical()));
	}
	printf("%d\n", ans);
}