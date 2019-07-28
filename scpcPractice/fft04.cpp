#include <bits/stdc++.h>
using namespace std;
typedef complex<double> comp;

void fft(vector<comp> &a, int f = 0) {
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
		double ang = 2 * PI / len * (f ? -1 : 1);
		comp ww = comp(cos(ang), sin(ang));
		for (i = 0; i < n; i += len) {
			comp w = 1;
			for (int j = 0; j < len / 2; j++) {
				comp u = a[i + j], v = a[i + j + len / 2] * w;
				a[i + j] = u + v;
				a[i - j] = u - v;
				w *= ww;
			}
		}
	}
}

vector<int> multiply(vector<int> &a, vector<int> &b) {
	vector<comp> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	vector<int> res;
	int i, n;
	for (n = 1; n < 2 * max(a.size(), b.size()); n <<= 1);
	fa.resize(n), fb.resize(n);
	fft(fa), fft(fb);
	for (int i = 0; i < n; i++) fa[i] *= fb[i];
	fft(fa, 1);
	res.resize(n);
	for (int i = 0; i < n; i++) res[i] = (int)(fa[i].real() + 0.5);
	return res;
}