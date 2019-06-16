#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll k;
ll arr[100010];
int cnt[100010];
ll sum, ans;
int n;
int main() {
	scanf("%d %lld", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%lld", &arr[i]);
		cnt[i] = n;
	}
	int a = 0;
	
	for (int b = 0; b < n; b++) {
		sum += arr[b];
		while (sum >= k) {
			sum -= arr[a];
			cnt[a] = b;
			a++;
		}
	}
	for (int i = 0; i < n; i++) {
		ans += (n - cnt[i]);
	}
	printf("%lld\n", ans);
}