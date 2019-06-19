#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll A[3], D, ans;
int main() {
	scanf("%lld %lld %lld %lld", &A[0], &A[1], &A[2], &D);
	sort(A, A + 3);
	ll aa = A[1] - A[0];
	ll bb = A[2] - A[1];
	if (aa < D) ans += D - aa;
	if (bb < D) ans += D - bb;
	printf("%lld\n", ans);
}