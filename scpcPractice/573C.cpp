#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, p[100010], ans;
ll m, k;
ll cnt;
ll getBlock(ll num) {
	num -= (cnt+1);
	return (num / k)+1;
}

ll lastBlock(ll Blocknum) {
	return Blocknum*k + cnt;
}


int main() {
	scanf("%lld %lld %lld", &n, &m, &k);
	for (int i = 0; i < m; i++) {
		scanf("%lld", &p[i]);
	}
	for (int i = 0; i < m;) {
		ll block = getBlock(p[i]);
		ll lastBlocknum = lastBlock(block);
		while (p[i] <= lastBlocknum) {
			i++;
			cnt++;
		}
		ans++;
	}
	printf("%lld\n", ans);
}