#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int q, n;
ll k, ans;
ll arr[110];
int main()
{
	scanf("%d", &q);
	while (q--) {
		scanf("%d %lld", &n, &k);
		for (int i = 0; i < n; i++) {
			scanf("%lld", &arr[i]);
		}
		sort(arr, arr + n);
		ll l = arr[0] + k;
		ll r = arr[n - 1] - k;
		if (l < r) {
			ans = -1;
		}
		else {
			ans = l;
		}
		printf("%lld\n", ans);
	}
}