#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int q;
ll k, n, a, b, ans;
int main() {
	scanf("%d", &q);
	for (int i = 0; i < q; i++) {
		scanf("%lld %lld %lld %lld", &k, &n, &a, &b);
		k -= n*b;
		a -= b;
		if (k <= 0) {
			ans = -1;
		}
		else {
			k--;
			ans = k / a;
		}
		ans = min(ans, n);
		printf("%lld\n", ans);
	}
}