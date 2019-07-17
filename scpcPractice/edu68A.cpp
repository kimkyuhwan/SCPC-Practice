#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int T;
ll n, x;
int main()
{
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		scanf("%lld %lld", &n, &x);
		printf("%lld\n", x * 2);
	}
	return 0;
}