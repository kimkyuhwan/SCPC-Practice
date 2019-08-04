#include <bits/stdc++.h>
using namespace std;
typedef complex<double> comp;
typedef long long ll;
void fft(vector<comp> &a, int inspect = 0) {
	int n = a.size();
	int i, j, len;
	const double PI = acos(-1.0);

	for (i = 1, j = 0; i < n; i++) {
		int bit = (n >> 1);
		for (; j >= bit; bit >>= 1) j -= bit;
		j += bit;
		if (i < j) swap(a[i], a[j]);
	}

	for (len = 2; len <= n; len <<= 1) {
		double ang = 2 * PI / len * (inspect ? -1 : 1);
		comp wlen = comp(cos(ang), sin(ang));
		for (i = 0; i < n; i += len) {
			comp w = 1;
			for (j = 0; j < len / 2; j++) {
				comp u = a[i + j], v = a[i + j + len / 2]*w;
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				w *= wlen;
			}
		}
	}
	if (inspect) for (i = 0; i < n; i++) a[i] /= n;
}

vector<ll> multiple(vector<ll> &a, vector<ll> &b) {
	vector<ll> res;
	vector<comp> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	int n, i;
	for (n = 1; n < 2 * max(a.size(), b.size()); n <<= 1);
	fa.resize(n), fb.resize(n);
	fft(fa), fft(fb);
	for (i = 0; i < n; i++) fa[i] *= fb[i];
	fft(fa, 1);
	res.resize(n);
	for (i = 0; i < n; i++) res[i] = (ll)(fa[i].real() + 0.5);
	return res;
}

int N;
vector<ll> aa, bb;
int main()
{
	scanf("%d", &N);
	aa.resize(N * 2);
	bb.resize(N); 
	for (int i = 0; i < N; i++) {
		scanf("%lld", &aa[i]);
		aa[i + N] = aa[i];
	}
	for (int i = N - 1; i >= 0; i--) {
		scanf("%lld", &bb[i]);
	}
	vector<ll> res = multiple(aa, bb);
	ll ans = 0;
	for (int i = N - 1; i < 2 * N; i++) {
		ans = max(ans, res[i]);
	}
	printf("%lld\n", ans);
}