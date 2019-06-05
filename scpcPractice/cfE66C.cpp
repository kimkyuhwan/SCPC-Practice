#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int T;
int n, k;
ll x[200010];
ll ans;
int main() {
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		ll minn = 1e9;
		scanf("%d %d", &n, &k);
		for (int j = 0; j < n; j++) {
			scanf("%lld", &x[j]);
		}
		for (int j = 0; j < n-k; j++) {
			ll mid = (x[j] + x[j + k]) / 2;
			ll val = max(abs(x[j] - mid), abs(x[j+k] - mid));
			if (minn > val) {
				minn = val;
				ans = mid;
			}
		}

		printf("%lld\n", ans);
	}
}