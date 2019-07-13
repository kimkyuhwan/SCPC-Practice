#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX = 100000;

struct LinearFunc {
	ll a, b;
	double s;
	LinearFunc() : LinearFunc(1, 0) {}
	LinearFunc(ll a1, ll b1) : a(a1), b(b1), s(0) {}
};

inline double cross(LinearFunc &f, LinearFunc &g) {
	return (g.b - f.b) / (f.a - g.a);
}

int N, A[MAX], B[MAX];
ll dp[MAX];
LinearFunc f[MAX];
int top;

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++) scanf("%d", &A[i]);
	for (int i = 0; i < N; i++) scanf("%d", &B[i]);
	for (int i = 1; i < N; i++) {
		LinearFunc g(B[i - 1], dp[i - 1]);
		while (top > 0) {
			g.s = cross(f[top - 1], g);
			if (f[top - 1].s < g.s) break;
			--top;
		}
		f[top++] = g;

		ll x = A[i];
		int fpos = top - 1;
		if (x < f[top - 1].s) {
			int lo = 0, hi = top - 1;
			while (lo + 1 < hi) {
				int mid = (lo + hi) >> 1;
				(x < f[mid].s ? hi : lo) = mid;
			}
			fpos = lo;
		}
		dp[i] = f[fpos].a * x + f[fpos].b;
	}
	printf("%lld\n", dp[N - 1]);
}