#include <bits/stdc++.h>
using namespace std;
int N, K;
typedef long long ll;

using ull = unsigned long long;

ull mul(ull x, ull y, ull m) {
	return (ull)((ll)x * y % m);
}
ull lpow(ull x, ull y, ull m) {
	ull r = 1;
	x %= m;
	while (y) {
		if (y & 1) r = mul(r, x, m);
		x = mul(x, x, m);
		y >>= 1;
	}
	return r;
}
bool MR(ull n, ull a) {
	if (n%a == 0) return 0;
	int cnt = -1;
	ull d = n - 1;
	while (!(d & 1)) {
		d >>= 1;
		cnt++;
	}
	ull p = lpow(a, d, n);
	if (p == 1 or p == n - 1) return 1;
	while (cnt--) {
		p = mul(p, p, n);
		if (p == n - 1) return 1;
	}
	return 0;
}

bool isPrime_MR(ll n) {
	for (auto p : { 2,3,5,7,11,13,17,19,23,29,31,37 }) {
		if (n == p) return 1;
		if (n > 40 && !MR(n, p)) return 0;
	}
	if (n <= 40) return 0;
	return 1;
}

int main() {
	scanf("%d", &N);
	int sol = 0;
	for (int i = 0; i < N; i++) {
		scanf("%d", &K);
		ll S = (ll)K * 2 + 1;
		if (!isPrime_MR(S)) {
			sol++;
		}
	}
	printf("%d\n", N-sol);
}