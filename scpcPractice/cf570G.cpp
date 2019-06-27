#include <bits/stdc++.h>
using namespace std;
#define INF 1e18
typedef long long ll;
int q, n;
ll val, sb;
int main() {
	scanf("%d", &q);
	while (q--) {
		map<ll, ll> mmap, mmap2;
		map < ll, vector<pair<ll, ll> > > flip;
		set<ll> visited, visited2;
		ll ans = 0;
		ll ans2 = 0;
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%lld %lld", &val, &sb);
			mmap[val]++;
			if (sb == 1) {
				mmap2[val]++;
			}
		}
		for (auto it = mmap.begin(); it != mmap.end(); it++) {
			flip[-it->second].push_back({ mmap2[it->first] , it->first });
		}

		ll cur = INF, cur2 = INF;
		vector<ll> sol;
		for (auto it = flip.begin(); it != flip.end(); it++) {
			cur = min(cur, -it->first);
			sort(it->second.rbegin(), it->second.rend());
			for (int j = 0; j < it->second.size() && cur>0; j++) {
				int zero = -it->first	 - it->second[j].first;
				int consume = max(j - zero, 0);
				sol.push_back(it->second[j].first - consume);
			}
			for (int j = 0; j < it->second.size() && cur>0; j++) {
				bool is_in = visited.find(cur) != visited.end();
				if (is_in) {
					cur--;
				}

				ans += cur;
				if (cur != 0) {
					visited.insert(cur);
				}
			}
		}
		sort(sol.rbegin(), sol.rend());
		int ccnt = 0;
		for (int j = 0; j < visited.size(); j++) {
			ll here = sol[j];
			ans2 += here;
		}
		printf("%lld %lld\n", ans, ans2);
	}
}
