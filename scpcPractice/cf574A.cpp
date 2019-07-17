#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int cnt[1010];
int n, k, val;
int main()
{
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d", &val);
		cnt[val]++;
	}
	int kk = n / 2 + (n % 2);
	int ans = 0;
	for (int i = 1; i <= k && kk; i++) {
		if (cnt[i] % 2 == 0) {
			ans += cnt[i];
			cnt[i] /= 2;
			kk -= cnt[i];
			cnt[i] = 0;
		}
		else if(cnt[i] > 2){
			ans += cnt[i];
			cnt[i] /= 2;
			kk -= cnt[i];
			ans--;
			cnt[i] = 1;
		}
	}
	for (int i = 1; i <= k && kk; i++) {
		if (cnt[i] !=0) {
			kk--;
			ans++;
			cnt[i] = 0;
		}
	}
	printf("%d\n", ans);
}