#include <bits/stdc++.h>
using namespace std;
int N, T, P, ans;
int dp[16][16];
int ttime[15];
int cost[15];

int solution(int currentTime, int prevTime) {
	int &ret = dp[currentTime][prevTime];
	if (ret != -1) return ret;
	if (currentTime + ttime[currentTime] > N + 1) return 0;
	ret = cost[currentTime];
	int next = 0;
	for (int i = currentTime + ttime[currentTime]; i <= N; i++) {
		next = max(next, solution(i, currentTime));
	}
	return ret+= next;
}


int main() {
	memset(dp, -1, sizeof(dp));
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d %d", &ttime[i], &cost[i]);
	}
	ans = solution(0, 0);
	printf("%d\n", ans);
}