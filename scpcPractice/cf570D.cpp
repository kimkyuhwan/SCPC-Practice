#include <bits/stdc++.h>
using namespace std;
#define INF 1e18
typedef long long ll;
int q, n;
ll val;
int main() {
	scanf("%d", &q);
	while(q--){
		map<ll, ll> mmap;
		map<ll, ll> flip;
		set<ll> visited;
		ll ans = 0;
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%lld", &val);
			mmap[val]++;
		}
		for (auto it = mmap.begin(); it != mmap.end(); it++) {
			flip[-it->second]++;
		}
		ll cur = INF;
		for (auto it = flip.begin(); it != flip.end(); it++) {
			cur = min(cur, -it->first);
			for (int j = 0; j < it->second && cur>0; j++) {
				bool is_in = visited.find(cur) != visited.end();
				if(is_in) {
					cur--;
				}
				ans += cur;
				visited.insert(cur);
			}
			if (cur == 0) break;
		}
		printf("%lld\n", ans);
	}
}