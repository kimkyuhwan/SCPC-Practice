#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll dp[20] = { 1,1,2,4 };
int N, T;
int main() {
	for (int i = 4; i <= 11; i++) {
		dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
	}
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		scanf("%d", &N);
		printf("%lld\n", dp[N]);
	}
}