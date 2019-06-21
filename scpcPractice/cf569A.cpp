#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll dp[110];
int main(){
	scanf("%d", &n);
	dp[1] = 1;
	for (int i = 2; i <= 100; i++) {
		dp[i] = dp[i - 1] + (i - 1) * 4;
	}
	printf("%lld\n", dp[n]);
}