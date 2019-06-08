#include <bits/stdc++.h>
using namespace std;
#define MOD 998244353
typedef long long ll;
int N;
ll ans;
vector<ll> A, B;
int main() {
	scanf("%d", &N);
	A.resize(N);
	B.resize(N);
	for (ll i = 0; i < N; i++) {
		scanf("%lld", &A[i]);
		A[i] *= (i + 1)*(N - i);
	}
	sort(A.begin(), A.end());
	for (ll i = 0; i < N; i++) {
		scanf("%lld", &B[i]);
	}
	sort(B.rbegin(), B.rend());
	for (int i = 0; i < N; i++) {
		ll a = A[i]%MOD;
		ll b = B[i]%MOD;
		ans = (ans + (a*b) % MOD) % MOD;
	}
	printf("%lld\n", ans);
}