#include <bits/stdc++.h>
using namespace std;
#define MOD (int)(1e9+7)
typedef long long ll;
vector<vector<ll> > A[128]= {};

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
	ll temp = square(c, pos);
	ret = square(temp, pos+1);
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
					A[N + 1][i][j] += ((A[N][i][k]%MOD) * (A[N][k][j]%MOD))%MOD;
				A[N + 1][i][j] %= MOD;
			}
	}
}

vector<vector<ll> > getGop(vector<vector<ll> > A, vector<vector<ll> > B) {
	vector<vector<ll> > ret;
	ret.resize(3, vector<ll>(3));
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			ret[i][j] += (A[i][j] + B[i][j])%MOD;
			ret[i][j] %= MOD;
		}
	return ret;
}
ll f[3], n, c;
vector<vector<ll> >  gop;
int main() {
	for (int i = 0; i < 128; i++) {
		A[i].resize(3, vector<ll>(3));
	}
	gop.resize(3, vector<ll>(3));
	A[0][0][0] = 1, A[0][0][1] = 1, A[0][0][2] = 1;
	A[0][1][0] = 1, A[0][1][1] = 2, A[0][1][2] = 2;
	A[0][2][0] = 2, A[0][2][1] = 3, A[0][2][2] = 4;
	gop[0][0] = 0, gop[0][1] = 0, gop[0][2] = 0;
	gop[1][0] = 0, gop[1][1] = 0, gop[1][2] = 0;
	gop[2][0] = 0, gop[2][1] = 0, gop[2][2] = 0;
	zegop();
	cin >> n;
	for (int i = 0; i < 3; i++) {
		cin >> f[i];
	}
	cin >> c;
	int cnt = 0;
	ll fibo[3];
	for (int i = 0; i < 3; i++) {
		fibo[i] = 1;
	}
	ll ans = getC(n - 3, c);
	n--;
	int idx = n % 3;
	n /= 3;
	cnt = 0;
	
	while (n) {
		if (n % 2) {
			gop = getGop(gop, A[cnt]);
		}
		cnt++;
		n >>= 1;
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			fibo[i] *= square(f[j], gop[i][j]);
			fibo[i]%=MOD;
		}
	}
	ans = (ans*fibo[idx]) % MOD;
	cout << ans << endl;
}