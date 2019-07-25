#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1e5 + 7;
struct linearFunc {
	ll a, b;
	double startDot;
	linearFunc() : linearFunc(1, 0) {}
	linearFunc(ll a, ll b) :a(a), b(b),startDot(0){}
};

inline double getCross(linearFunc &f, linearFunc s) {
	return (s.b - f.b) / (f.a - s.a);
}
int N, top;
ll a[MAXN], b[MAXN];
ll dp[MAXN];
linearFunc f[MAXN];
int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) scanf("%lld", &a[i]);
	for (int i = 0; i < N; i++) scanf("%lld", &b[i]);
	for (int i = 1; i < N; i++) {
		linearFunc g(b[i - 1], dp[i-1]);
		while (top > 0) {
			g.startDot = getCross(f[top-1], g);
			if (f[top - 1].startDot < g.startDot) break;
			top--;
		}
		f[top++] = g;
		ll x = a[i];
		int fpos = top - 1;
		if (x < f[top - 1].startDot) {
			int lo = 0, hi = top - 1;
			while (lo + 1 < hi) {
				int mid = (lo + hi) >> 1;
				(x < f[mid].startDot ? hi : lo) = mid;
			}
			fpos = lo;
		}
		dp[i] = f[fpos].a * x + f[fpos].b;
	}
	printf("%lld\n", dp[N - 1]);
	return 0;
}