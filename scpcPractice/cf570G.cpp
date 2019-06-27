#include <bits/stdc++.h>
using namespace std;
#define INF 1e18
typedef long long ll;
int q, n;
ll val, sb;
int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &q);
	while (q--) {
		map<ll, ll> mmap, mmap2;
		map < ll, vector<pair<ll, ll> > > flip;
		set<ll> visited, visited2;
		ll ans = 0;
		ll ans2 = 0;
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%lld %lld", &val,&sb);
			mmap[val]++;
			if (sb == 1) {
				mmap2[val]++;
			}
		}
		for (auto it = mmap.begin(); it != mmap.end(); it++) {
			flip[-it->second].push_back({ mmap2[it->first] , it->first  });
		}

		ll cur = INF, cur2=INF;
		vector<ll> sol, sol2;
		int ccnt = 0;
		for (auto it = flip.begin(); it != flip.end(); it++) {
			cur = min(cur, -it->first);
			sort(it->second.rbegin(), it->second.rend());
			for (int j = 0; j < it->second.size(); j++) {
				int zero = -it->first - it->second[j].first;
				int consume = max(j-zero, 0);
				sol.push_back(it->second[j].first - consume);
				sol2.push_back(-it->first - j);
			}
		}
		sort(sol.rbegin(), sol.rend());
		sort(sol2.rbegin(), sol2.rend());
		for (int i = 0; i < sol2.size(); i++) {
			ll here = sol2[i];
			if (here <= 0) break;
			if (visited.find(here) == visited.end()) {
				visited.insert(here);
				ans += here;
			}
		}

		for (int j = 0; j < visited.size(); j++) {
			if (sol[j] <= 0) continue;
			ans2 += sol[j];
		}

		printf("%lld %lld\n", ans,ans2);
	}
}