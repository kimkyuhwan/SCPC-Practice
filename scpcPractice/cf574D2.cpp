#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353LL;
const ll maxx = 889069407LL;
ll cnt[110][10];
ll sum[110];
ll tsum[110];
ll l[110], lol[110];
int n;
char str[110];
ll ans;

void getCount(int i, int j) {
	ll ccnt = l[i]*l[j];
	if (ccnt == 0) return;
	int b = 0;
	bool visited[30] = {};
	if (i > j) {
		for (int a = 0; a < j; a++) {
			tsum[b] += (sum[a + 1] % mod) * (ccnt%mod);
			tsum[b] %= mod;
			visited[b] = true;
			b += 2;
		}
		b = 1;
		for (int a = 0; a < i; a++) {
			tsum[b] += (sum[a + 1] % mod) * (ccnt%mod);
			tsum[b] %= mod;
			visited[b] = true;
			while (visited[b]) b++;
		}
	}
	else {
		b = 1;
		for (int a = 0; a < i; a++) {
			tsum[b] += (sum[a + 1] % mod) * (ccnt%mod);
			tsum[b] %= mod;
			visited[b] = true;
			b += 2;
		}
		b = 0;
		for (int a = 0; a < j; a++) {
			tsum[b] += (sum[a + 1] % mod) * (ccnt%mod);
			tsum[b] %= mod;
			visited[b] = true;
			while (visited[b]) b++;
		}
	}
}


int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf(" %s", str);
		int len = strlen(str);
		for (int j = 0; j < len; j++) {
			cnt[len - j][str[j] - '0']++;
		}
		l[len]++;
	}
	for (int i = 0; i <= 10; i++) {
		for (int j = 0; j < 10; j++) {
			sum[i] += (cnt[i][j])*j;
			sum[i] %= mod;
		}
	}
	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 10; j++) {
			getCount(i, j);
		}
	}
	for (int i = 0; i <= 20; i++) {
		ll val = 1;
		for (int j = 0; j < i; j++) {
			val *= 10;
			val %= mod;
		}
		ans += (tsum[i] % mod) * (val%mod);
		ans %= mod;
	}
	printf("%lld\n", ans);
}