#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int mod = 1e9 + 7;
vector<lint> dp;
lint N, M;

lint ipow(lint x, lint y) {
	lint ret = 1;
	lint piv = x;
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

vector<lint> massey(vector<lint> x) {
	vector<lint> cur, ls;
	int lf, ld;
	for (int i = 0; i < x.size(); i++) {
		lint t = 0;
		for (int j = 0; j < cur.size(); j++) {
			t = (t + 1ll * x[i - j - 1] * cur[j]) % mod;
		}
		if ((t - x[i]) % mod == 0) continue;
		if (cur.empty()) {
			cur.resize(i + 1);
			lf = i;
			ld = (t - x[i]) % mod;
			continue;
		}
		lint k = ((t - x[i]) * ipow(ld, mod - 2)) % mod;
		vector<lint> c(i - lf - 1);
		c.push_back(k);
		for (auto &j : ls) c.push_back((-j*k) % mod);
		if (cur.size() > c.size()) c.resize(cur.size());
		for (int j = 0; j < cur.size();j++) c[j] = (c[j] + cur[j]) % mod;
		if (i - lf + ls.size() >= cur.size()) {
			tie(ls, lf, ld) = make_tuple(cur, i, (t - x[i])%mod);
		}
		cur = c;
	}
	for (auto &i : cur) i = (i%mod + mod) % mod;
	return cur;
}

lint get_nth(vector<lint> x, vector<lint> dp, lint N) {
	int m = x.size();
	vector<lint> s(m), t(m);
	s[0] = 1;
	if (m != 1) t[1] = 1;
	else t[0] = x[0];

	auto mul = [&x](vector<lint> v, vector<lint> w) {
		int m = v.size();
		vector<lint> t(2 * m);

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < m; j++) {
				t[i + j] += (1ll * v[i] * w[j]) % mod;
				if (t[i + j] > mod) t[i + j] -= mod;
			}
		}
		for (int i = 2*m-1; i >=m; i--) {
			for (int j = 1; j <= m; j++) {
				t[i - j] += (1ll * t[i] * x[j-1]) % mod;
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
	lint ret = 0;
	for (int i = 0; i < m; i++) ret = (ret + 1ll * s[i] * dp[i]) % mod;
	return ret;
}

lint solution(vector<lint> x, lint N) {
	if (x.size() > N) return x[N];
	vector<lint> v = massey(x);
	if (v.empty()) return 0;
	return get_nth(v, x, N);
}

int main() {
	scanf("%lld %lld", &N, &M);
	lint K = 3 * M;
	dp.resize(K);
	dp[0] = 1;
	for (int i = 1; i < K; i++) {
		dp[i] = dp[i - 1];
		if (i >= M) {
			dp[i] = (dp[i] + dp[i - M])%mod;
		}
	}
	printf("%lld\n", solution(dp,N));
}