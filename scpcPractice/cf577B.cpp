#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll sum, val, maxx;
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%lld", &val);
		sum += val;
		maxx = max(val, maxx);
	}
	if (sum % 2 == 0 && maxx <= sum /2) {
		puts("YES");
	}
	else {
		puts("NO");
	}
}