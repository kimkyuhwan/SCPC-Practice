#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll val, sol, ans=1;

ll gcd(ll a, ll b) {
	if (a < b) swap(a, b);
	if (a%b == 0) return b;
	return gcd(b, a%b);
}

int main() {
	scanf("%d", &n);
	scanf("%lld", &sol);
	for (int i = 1; i < n; i++) {
		scanf("%lld", &val);
		sol = gcd(sol, val);
	}
	ll sq = sqrt(sol);
	for (ll i = 2; i <= sq; i++) {
		ll cnt = 0;
		while (sol%i == 0) {
			sol /= i;
			cnt++;
		}
		ans *= (cnt+1);
	}
	if (sol != 1) {
		ans *= 2;
	}
	printf("%lld\n", ans);
} 