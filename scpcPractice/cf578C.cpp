#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, m, q, g;

ll gcd(ll a, ll b) {
	if (a < b) swap(a, b);
	if (a%b == 0) return b;
	return gcd(b, a%b);
}
	
int main() {	
	ll s1, s2, e1, e2;
	scanf("%lld %lld %lld", &n, &m, &q);
	g = gcd(n, m);
	ll aa = n / g;
	ll bb = m / g;
	for (int i = 0; i < q; i++) {
		scanf("%lld %lld %lld %lld",&s1,&s2,&e1,&e2);
		s2--, e2--;
		ll gA = (s1 == 1) ? s2 / aa : s2 / bb;
		ll gB = (e1 == 1) ? e2 / aa : e2 / bb;
		if (gA == gB) {   
			puts("YES");
		}	
		else {
			puts("NO");
		}
	}
	return 0;
}