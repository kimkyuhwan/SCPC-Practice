#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int mod = 1e9 + 7;
vector<lint> dp = { 0,1,1,2,3,5,8,13,21 };
lint N;

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
	int ld, lf;
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
		lint k = (t - x[i]) * ipow(ld, mod - 2) % mod;
		vector<lint> c(i - lf - 1);
		c.push_back(k);
		for (auto &j : ls) c.push_back(-j * k %mod);
		if (c.size() < cur.size()) c.resize(cur.size());
		for (int j = 0; j < cur.size(); j++) {
			c[j] = (c[j] + cur[j]) % mod;
		}
		if (i - lf + ls.size() >= cur.size()) {
			tie(ls, lf, ld) = make_tuple(cur, i, (t - x[i])%mod);
		}
		cur = c;
	}
	for (auto &i : cur) i = (i%mod + mod) % mod;
	return cur;
}

lint get_nth(vector<lint> x, vector<lint> dp, lint n) {
	int m = x.size();
	vector<lint> s(m), t(m);
	s[0] = 1;
	if (m != 1) {
		t[1] = 1;
	}
	else {
		t[0] = x[0];
	}
	auto mul = [&x](vector<lint> v, vector<lint> w) {
		int m = v.size();
		vector<lint> t(2 * m);
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < m; k++) {
				t[j + k] += 1ll * v[j] * w[k] % mod;
				if (t[j + k] > mod) t[j + k] -= mod;
			}
		}
		for (int j = 2*m-1; j >=m; j--) {
			for (int k = 1; k <= m; k++) {
				t[j - k] += 1ll * t[j] * x[k-1] % mod;
				if (t[j - k] > mod) t[j - k] -= mod;
			}
		}
		t.resize(m);
		return t;
	};
	while (n) {
		if (n & 1) s = mul(s, t);
		t = mul(t, t);
		n >>= 1;
	}
	lint ret = 0;
	for (int i = 0; i < m; i++) ret += 1ll * s[i] * dp[i] % mod;
	return ret % mod;
}


lint solution(vector<lint> x, lint N) {
	if (x.size() > N) return x[N];
	vector<lint> vec = massey(x);
	if (vec.empty()) return 0;
	return get_nth(vec, x, N);
}


int main() {
	scanf("%lld", &N);
	printf("%lld\n", solution(dp, N));

}