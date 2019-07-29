#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
typedef long long ll;

vector<ll> dp = { 0,1,1,2,3,5,8,13 };
int N;

ll ipow(ll x, ll y) {
	ll ret = 1;
	ll piv = x;
	while (y) {
		if (y & 1) {
			ret *= piv;
			ret %= mod;
		}
		piv = (piv*piv) % mod;
		y >>= 1;
	}
	return ret;
}

vector<ll> massey(vector<ll> v) {
	int n = v.size();
	vector<ll> cur, ls;
	int ld, lf;
	for (int i = 0; i < n; i++) {
		ll t = 0;
		for (int j = 0; j < cur.size(); j++) {
			t = (t + 1ll * v[i - j - 1] * cur[j]) % mod;
		}
		if ((t - v[i]) % mod == 0) continue;
		if (cur.empty()) {
			cur.resize(i + 1);
			lf = i;
			ld = (t - v[i]) % mod;
			continue;
		}
		ll k = (((t - v[i])%mod)*ipow(ld, mod - 2)) % mod;
		vector<ll> c(i - lf - 1);
		c.push_back(k);
		for (auto &j : ls) c.push_back((-j*k) % mod);
		if (cur.size() > c.size()) c.resize(cur.size());
		for (int j = 0; j < cur.size(); j++) c[j] = (c[j] + cur[j]) % mod;
		if (i - lf + ls.size() >= cur.size()) {
			tie(ls, lf, ld) = make_tuple(cur, i, (t - v[i]) % mod);
		}
		cur = c;
	}
	for (auto &i : cur) i = (i%mod + mod) % mod;
	return cur;
}

ll get_nth(vector<ll> x, vector<ll> dp, ll N) {
	int m = x.size();
	vector<ll> s(m), t(m);
	s[0] = 1;
	if (m != 1) {
		t[1] = 1;
	}
	else {
		t[0] = x[0];
	}

	auto mul = [&x](vector<ll> v, vector<ll> w) {
		int m = v.size();
		vector<ll> t(2 * m);
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < m; j++) {
				t[i + j] += ((1ll * v[i] * w[j])%mod);
				if (t[i + j] > mod) t[i + j] -= mod;
			}
		}
		for (int i = 2*m-1; i >=m; i--) {
			for (int j = 1; j <= m; j++) {
				t[i - j] += ((1ll * t[i] * x[j-1]) % mod);
				if (t[i - j] > mod) t[i - j] -= mod;
			}
		}
		t.resize(m);
		return t;
	};
	while (N) {
		if (N & 1) s = mul(s, t);
		t = mul(t, t);
		N >>= 1;
	}
	ll ret = 0;
	for (int i = 0; i < m; i++) ret = (ret + 1ll * s[i] * dp[i]) % mod;
	return ret;
}


ll solution(vector<ll> x, int N) {
	if (x.size() > N) return x[N];
	vector<ll> v = massey(x);
	if (v.empty()) return 0;
	return get_nth(v, x, N);
}


int main() {
	scanf("%d", &N);

	printf("%lld\n", solution(dp, N));


}