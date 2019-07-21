#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int w, h;
ll ans = 1LL;
int main()
{
	scanf("%d %d", &w, &h);
	int gop = w+h;

	for (int i = 0; i < gop; i++) {
		ans *= 2;
		ans %= 998244353LL;
	}
	printf("%lld\n", ans);
}