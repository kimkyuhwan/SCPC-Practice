#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll l, r, x, y, k;
int ans;
int main() {
	scanf("%lld %lld %lld %lld %lld", &l, &r, &x, &y, &k);
	for (ll i = x; i <= y; i++) {
		ll temp = i*k;
		if (temp >= l && temp <= r) {
			ans = 1;
		}
	}
	if (ans) puts("YES");
	else puts("NO");
}