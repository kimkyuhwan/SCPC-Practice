#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, k;
ll arr[300010];
ll ans = 0;
ll psum[300010];
vector<ll> pos;

int main() {
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%lld", &arr[i]);
	for (int i = n; i >= 1; i--) {
		psum[i] = psum[i + 1] + arr[i];
		if (i != 1) {
			pos.push_back(psum[i]);
		}
	}
	ans = psum[1];
	sort(pos.rbegin(), pos.rend());
	for (int i = 0; i < k-1; i++)
		ans += pos[i];
	printf("%lld\n", ans);
	return 0;
}