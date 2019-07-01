#include <bits/stdc++.h>
using namespace std;
char str[200010];
char temp[200010];
int N, M;
int psum[200010][26];
int tempSum[26];
void initString() {
	for (int i = 0; i < N; i++) {
		int curr = str[i] - 'a';
		psum[i][curr] = 1;
		for (int j = 0; j < 26; j++) {
			if (i > 0) {
				psum[i][j] += psum[i - 1][j];
			}
		}
	}
}
bool isPossible(int val) {
	for (int i = 0; i < 26; i++) {
		if (psum[val][i] >= tempSum[i]) continue;
		return false;
	}
	return true;
}

int main() {
	scanf("%d", &N);
	scanf(" %s", str);
	scanf(" %d", &M);
	initString();

	for (int i = 0; i < M; i++) {
		memset(tempSum, 0, sizeof(tempSum));
		scanf(" %s", temp);
		int l = 0, r = N;
		int sz = strlen(temp);
		for (int j = 0; j < sz; j++) {
			int curr = temp[j] - 'a';
			tempSum[curr]++;
		}
		while (l < r) {
			int mid = (l + r) >> 1;
			if (isPossible(mid)) {
				r = mid;
			}
			else {
				l = mid + 1;
			}
		}
		printf("%d\n", l+1);
	}
}