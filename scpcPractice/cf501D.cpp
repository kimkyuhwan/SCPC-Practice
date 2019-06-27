#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, k, s;
ll maD;
ll cur = 1;
vector<ll> ans;
int main() {
	scanf("%lld %lld %lld", &n, &k, &s);
	maD = n - 1;
	if (maD * k < s || k>s) {
		puts("NO");
		return 0;
	}
	ll pos = s / k;
	ll r = s%k;
	ans.resize(k, pos);
	for (int i = 0; i < r; i++) {
		ans[i]++;
	}
	puts("YES");
	for (int i = 0; i < k; i++) {
		if (i % 2 == 0) cur += ans[i];
		else cur -= ans[i];
		printf("%lld ", cur);
	}
}