#include <bits/stdc++.h>
using namespace std;
int n, x, sum, val, ans;
int main() {
	scanf("%d %d", &n, &x);
	ans = 1;
	for (int i = 0; i < n; i++) {
		scanf("%d", &val);
		sum += val;
		if (sum <= x) {
			ans++;
		}
	}
	printf("%d\n", ans);
}