#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int T;
ll val;
int main()
{
	scanf("%d", &T);
	for (int i = 0; i < T; i++){
		ll sum = 0;
		for (int j = 0; j < 3; j++) {
			scanf("%lld", &val);
			sum += val;
		}
		printf("%lld\n", sum/2);
	}
	return 0;
}