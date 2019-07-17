#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int T;
ll n, k;
int ans = 0;
int main() {
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		ans = 0;
		scanf("%lld %lld", &n, &k);
		if (n == 0) ans = 1;
		else if (n == k) ans = 0;
		else if (n < k || k % 3 != 0) {
			if (n % 3 == 0) {
				ans = 1;
			}
			else {
				ans = 0;
			}
		}
		else if (k % 3 == 0) {
			int mod = k + 1;
			n -= mod;
			
			if (n%mod == k) {
				ans = 0;
			}
			else if ((n%mod) % 3 == 0) {
				ans = 1;
			}
		}
		if (ans) {
			puts("Bob");
		}
		else {
			puts("Alice");
		}
	}
}