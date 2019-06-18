#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, k, ans, tower;
ll cnt[200010];
ll last = 0;
int main() {
	scanf("%lld %lld", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%lld", &tower);
		cnt[tower]++;
		last = max(last, tower);
	}	ll sum = 0;
	ll temp = 0;
	ll cost=0;
	for (int i = 1; i <= last; i++) {
		cnt[i] += cnt[i - 1];
	}
	bool flag = false;
	for (int i = 1; i <last; i++) {
		cost = (n - cnt[i]);
		if (cost == n) continue;
		if (!flag) {
			flag++;
			temp++;
		}
		if (sum + cost > k) {
			sum = 0;
			temp++;
		}
		sum += cost;
	}
	ans = temp;
	sum = temp = 0;
	flag = false;
	for (int i = last-1; i >= 1; i--) {
		cost = (n - cnt[i]);
		if (cost == n) continue;
		if (!flag) {
			flag++;
			temp++;
		}
		if (sum + cost > k) {
			sum = 0;
			temp++;
		}
		sum += cost;
	}
	ans = min(ans, temp);
	printf("%lld\n", ans);
}