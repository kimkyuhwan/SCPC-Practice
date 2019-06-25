#include <bits/stdc++.h>
using namespace std;
int T, N;
int arr[100010][2];
int dp[100010][2];

int solution(int pos, int y) {
	if (pos >= N) return 0;
	int &ret = dp[pos][y];
	if (ret != -1) return ret;
	ret = arr[pos][y];
	int next = 0;
	next = max(next, solution(pos + 1, (y + 1) % 2));
	for (int i = 0; i < 2; i++)
		next = max(next, solution(pos + 2, i));
	return ret+=next;
}

int main() {
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		memset(dp, -1, sizeof(dp));
		scanf("%d", &N);
		for (int k = 0; k < 2; k++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &arr[j][k]);
			}
		}
		int ans = max(solution(0, 0), solution(0, 1));
		printf("%d\n", ans);
	}
}