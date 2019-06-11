#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int N;
ll ans;
int main() {
	scanf("%d", &N);
	if (N % 2 == 1) {
		ans = 0;
	}
	else {
		ans = 1;
		for (int i = 0; i < N/2; i++)
			ans *= 2;
	}
	printf("%lld\n", ans);
}