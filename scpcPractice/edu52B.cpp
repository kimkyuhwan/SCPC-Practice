#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N, M;

int main() {
	scanf("%lld %lld", &N, &M);
	ll maxx = M * 2;
	ll minn = M + 1;
	for (ll i = 1; i <= N; i++) {
		ll sum = i*(i - 1) / 2;
		if (sum < M) {
			minn = i;
		}
		else {
			minn = i;
			break;
		}
	}
	ll A = max(0LL, N - maxx);
	ll B = max(N - minn, A);
	printf("%lld %lld\n", A, B);
}