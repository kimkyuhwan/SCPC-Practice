#include <bits/stdc++.h>
using namespace std;
int N, sum, ans;
int arr[110];
int dp[110];
int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &arr[i]);
		sum += arr[i];
	}
	for (int f = 1; f <= N; f++) {
		dp[f] = sum;
		if (arr[f] == 0) dp[f]++;
		else dp[f]--;
		ans = max(ans, dp[f]);
		for (int b = f+1; b <= N; b++) {
			if (arr[b] == 0) dp[f]++;
			else dp[f]--;
			ans = max(ans, dp[f]);
		}
	}
	printf("%d\n", ans);
}