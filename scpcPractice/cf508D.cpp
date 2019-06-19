#include <bits/stdc++.h>
using namespace std;
#define INF 1e18
typedef long long ll;
int N;
ll slime[500010];
ll ans, zero;
vector<ll> p, m;
int main() {
	scanf("%d", &N);
	if (N == 1) {
		scanf("%lld", &slime[0]);
		printf("%lld", slime[0]);
		return 0;
	}
	for (int i = 0; i < N; i++) {
		scanf("%lld", &slime[i]);
		if (slime[i] == 0) {
			zero++;
		}
		else if (slime[i] > 0) {
			p.push_back(slime[i]);
		}
		else {
			m.push_back(slime[i]);
		}
		ans += abs(slime[i]);
	}
	sort(p.begin(), p.end());
	sort(m.rbegin(), m.rend());
	if (zero==0 ) {
		if (m.empty()) {
			ans -= (p[0] + p[1]);
			ans += abs(p[0] - p[1]);
		}
		else if (p.empty()) {
			if (m.size() >= 2) {
				ans += (m[0] + m[1]);
				ans += abs(m[0] - m[1]);
			}
		}
	}
	printf("%lld\n", ans);
}