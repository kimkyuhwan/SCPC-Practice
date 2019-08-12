#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int T;
int n;
ll m, k;
ll h[110];
int main()
{
	scanf("%d", &T);
	while (T--) {
		scanf("%d %lld %lld", &n, &m, &k);
		for (int i = 0; i < n; i++) scanf("%lld", &h[i]);
		bool isPossible = true;
		ll curBlock = m;
		for (int i = 0; i < n - 1; i++) {
			ll nextHeight = h[i + 1] - k;
			nextHeight = max(0LL, nextHeight);
			if (h[i] >= nextHeight) {
				curBlock += (h[i]- nextHeight);
			}
			else {
				ll needs = nextHeight - h[i];
				if (needs > curBlock) {
					isPossible = false;
					break;
				}
				else {
					curBlock -= needs;
				}
			}
		}
		if (isPossible) {
			puts("YES");
		}
		else {
			puts("NO");
		}
	}
}