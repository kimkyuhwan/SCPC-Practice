#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int N, T;
ll ans, val[200010];
int main()
{
	scanf("%d", &T);
	for (int testcase = 1; testcase <= T; testcase++) {
		scanf("%d", &N);
		ans = 0;
		for (int i = 0; i < N; i++) {
			scanf(" %lld", &val[i]);
		}
		ans = 0;
		ll sum = (val[1] - val[0])*(val[1] - val[0]);
		for (int i = 2; i < N; i+=2) {
			ll l = (val[i] - val[i-1]);
			sum += l*l;
		}
		ans = max(ans, sum);
		sum = (val[1] - val[0])*(val[1] - val[0]);
		for (int i = N - 1; i > 1; i-=2) {
			ll l = (val[i] - val[i - 1]);
			sum += l*l;
		}
		ans = max(ans, sum);
		double aa = ans;
		printf("Case #%d\n", testcase);
		printf("%.9lf\n", aa);
	}
} 