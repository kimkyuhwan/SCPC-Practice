#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll sum, val;
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%lld", &val);
		sum += val;
	}
	if (sum % 2 == 0) {
		puts("YES");
	}
	else {
		puts("NO");
	}
}