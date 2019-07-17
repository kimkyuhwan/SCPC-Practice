#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353LL;
const ll maxx = 889069407LL;
ll cnt[110][10];
ll sum[110];
int n;
char str[110];
ll ans;
int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf(" %s", str);
		int len = strlen(str);
		for (int j = 0; j < len; j++) {
			cnt[len - j][str[j] - '0']++;
		}
	}
	for (int i = 0; i <= 10; i++) {
		for (int j = 0; j < 10; j++) {
			sum[i] += (cnt[i][j] * j*n);
			sum[i] %= mod;
		}
	}
	for (int i = 1; i <= 10; i++) {
		ll val = 11;
		for (int j = 1; j < i; j++) {
			val *= 100;
			val %= mod;
		}
		ans += (sum[i] % mod) * (val%mod);
		ans %= mod;
	}
	printf("%lld\n", ans);
}