#include <bits/stdc++.h>
using namespace std;
typedef complex<double> comp;

void fft(vector<comp> &a, int invert = 0) {
	int n = a.size();
	int i, j, len;
	double PI = acos(-1.0);
	for (int i = 1, j = 0; i < n; i++) {
		int bit = (n >> 1);
		for (; j >= bit; bit >>= 1) j -= bit;
		j += bit;
		if (i < j) swap(a[i], a[j]);
	}
	for (len = 2; len <= n; len <<= 1) {
		double ang = 2 * PI / len * (invert ? -1 : 1);
		comp wlen = comp(cos(ang), sin(ang));
		for (i = 0; i < n; i += len) {
			comp w = 1;
			for (j = 0; j < len / 2; j++) {
				comp u = a[i + j], v = a[i + j + len / 2];
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				w *= wlen;
			}
		}
	}
	if (invert) for(i=0;i<n;i++) a[i] /= n;
}

vector<int> multiple(vector<int> &a, vector<int> &b) {
	vector<int> res;
	vector<comp> pa(a.begin(), a.end()), pb(b.begin(), b.end());
	int i, n;
	for (n = 1; n < 2 * max(a.size(), b.size()); n *= 2);
	pa.resize(n), pb.resize(n);
	fft(pa), fft(pb);
	for (i = 0; i < n; i++) pa[i] *= pb[i];
	fft(pa, 1);
	res.resize(n);
	for (i = 0; i < n; i++) res[i] = (int)(pa[i].real() + 0.5);
	return res;
}

int main() {

}