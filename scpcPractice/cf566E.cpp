#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007
typedef long long ll;
ll A[128][3][3] = {};

ll square(ll pos, ll a) {
	ll ret = 1;
	while (a) {
		if (a % 2 == 1) {
			ret *= pos;
			ret %= MOD;
		}
		a >>= 1;
		pos = (pos*pos) % MOD;
	}
	return ret%MOD;
}

ll getC(ll pos, ll c) {
	ll ret = 1;
	if (pos <= 0) return 1;
	ll temp = pos;
	ll a = c;
	while (temp > 0) {
		if (temp % 2 == 1) {
			ret = (ret*a) % MOD;
		}
		a = (a*a) % MOD;
		temp >>= 1;
	}
	a = ret;
	ret = 1;
	temp = pos + 1;
	while (temp > 0) {
		if (temp % 2 == 1) {
			ret = (ret*a) % MOD;
		}
		a = (a*a) % MOD;
		temp >>= 1;
	}
	
	return ret%MOD;
}
void zegop()
{
	for (int N = 0; N < 127; N++)
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
			{
				for (int k = 0; k < 3; k++)
					A[N + 1][i][j] += A[N][i][k] * A[N][k][j];
				A[N + 1][i][j] %= MOD;
			}
	}
}
ll f[3], n, c;
int main() {
	A[0][0][0] = 0, A[0][0][1] = 0, A[0][0][2] = 1;
	A[0][1][0] = 1, A[0][1][1] = 1, A[0][1][2] = 1;
	A[0][2][0] = 1, A[0][2][1] = 2, A[0][2][2] = 2;
	zegop();
	cin >> n;
	for (int i = 0; i < 3; i++) {
		cin >> f[i];
	}
	cin >> c;
	int cnt = 0;
	ll fibo[3];
	for (int i = 0; i < 3; i++) {
		fibo[i] = f[i];
	}
	ll ans = getC(n - 3, c);
	int idx = n % 3;
	// 5 6 7 => 3 6 12 24 1=>4
	n -= 4;
	cnt = 1;
	while (n) {
		if (n % 3==0) {
			ll temp[3];
			for (int i = 0; i < 3; i++) {
				temp[i] = fibo[i];
				for (int j = 0; j < 3; j++) {
					temp[j] = square(f[j],A[cnt][i][j]);
					fibo[i] = (fibo[i]*temp[j])%MOD;
				}
			}
		}
		cnt++;
		n /= 3;
	}
	ans = (ans*fibo[0]) % MOD;
	cout << ans << endl;
}