#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int t;
int n, m, maxx;
int arr[1000010];
int cnt[1000010];
int tcnt[1000010];
ll psum[1000010];
ll sum;

ll getSum(int y, int x) {
	ll ret = 0;
	ll line = psum[x - 1] + psum[m - x];
	ret = line * n;
	ret += (psum[y - 1] + psum[n - y])*m;
	return ret;
}

int main() {
	scanf("%d", &t);
	for (int i = 0; i < t; i++) {
		scanf("%d", &arr[i]);
		maxx = max(maxx, arr[i]);
		sum += arr[i];
		cnt[arr[i]]++;
	}
	for (int i = 1; i <= 1000000; i++) {
		psum[i] = psum[i - 1] + i;
	}
	for (int i = 1; i <= sqrt(t); i++) {
		if (t%i == 0) {
			n = i, m = t / i;
			int k = n + m - maxx;
			if (maxx < (n / 2 + m / 2)) {
					continue;
			}
			for (int yy = 1; yy < k; yy++) {
				ll ssum = getSum(yy , k - yy);
				if (ssum == sum) {
					fill(tcnt, tcnt + maxx+1, 0);
					for (int y = 1; y <= n; y++) {
						for (int x = 1; x <= m; x++) {
							int val = (abs(y - yy) + abs(x - (k - yy)));
							tcnt[val]++;
						}
					}
					bool isPossible = true;
					for (int i = 0; i <= maxx; i++) {
						if (tcnt[i] != cnt[i]) {
							isPossible = false;
							break;
						}
					}
					if (isPossible) {
						printf("%d %d\n", n, m);
						printf("%d %d\n", yy, k - yy);
						return 0;
					}
				}
			}
		}
	}
	puts("-1");
	return 0;
}