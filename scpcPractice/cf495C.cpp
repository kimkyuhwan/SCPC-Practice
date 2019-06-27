#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, cnt, ans;
ll arr[100010];
bool visited[100010];
ll sum[100010];
int main() {
	scanf("%lld", &n);
	for (int i = 0; i < n; i++) {
		scanf("%lld", &arr[i]);
		sum[arr[i]] = cnt;
		if (!visited[arr[i]]) {
			visited[arr[i]] = true;
			cnt++;
		}
	}
	for (int i = 0; i <= 100000; i++) {
		ans += sum[i];
	}
	printf("%lld\n", ans);

}
