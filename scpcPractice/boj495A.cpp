#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define INF 1e18
ll N, D, ans;
set<ll> st;
ll val[110];
int main()
{
	scanf("%lld %lld", &N, &D);
	for (int i = 0; i < N; i++) {
		scanf("%lld", &val[i]);
		st.insert(val[i] - D);
		st.insert(val[i] + D);
	}
	ll pos = -INF;
	int idx = 0;
	for (auto it = st.begin(); it != st.end(); it++) {
		ll here = *it;
		int l = lower_bound(val, val + N, here) - val;
		if (l == N) {
			l--;
		}
		if (abs(val[l] - here) >= D) {
			if (l > 0) {
				if(abs(val[l - 1] - here) >= D){
					ans++;
				}
			}
			else {
				ans++;
			}
		}
	}
	printf("%lld\n", ans);
}