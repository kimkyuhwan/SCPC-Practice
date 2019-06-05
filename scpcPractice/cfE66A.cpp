#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int T;
ll n, k;

int main() {
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		scanf("%lld %lld", &n, &k);
		ll sol = 0;
		for (ll a = n; a > 0;) {
			ll s = (a / k) * k;
			sol += (a - s);
			a = s;
			if (a == 0) break;
			if (a%k == 0) {
				a /= k;
				sol++;
			}
		}
		printf("%lld\n", sol);
	}
}