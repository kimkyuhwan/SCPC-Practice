#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, k;
int main()
{
	scanf("%lld %lld", &n, &k);
	ll l = 0, r = 1e9;
	for (ll i = 0; i <= n; i++) {
		ll sum = (i*(i + 1)) / 2;
		ll sol = sum - (n - i);
		if (sol == k) {
			printf("%lld", n-i);
			return 0;
		}
	}
}