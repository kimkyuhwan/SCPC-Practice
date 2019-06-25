#include <bits/stdc++.h>
using namespace std;
#define MOD 10007
typedef long long ll;
int N;
ll dp[1010] = { 1,1,2};
int main() {
	scanf("%d", &N);
	for (int i = 3; i <= N; i++) {
		dp[i] = dp[i - 1] + dp[i - 2];
		dp[i] %= MOD;
	}
	printf("%lld\n", dp[N]);
}