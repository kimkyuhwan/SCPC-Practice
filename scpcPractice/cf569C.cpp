#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, q;
ll maxx=-1, idx;
ll arr[200010];
ll m;
pair<ll, ll> noRound[300010];
vector<ll> rnd;
deque<ll> dq;
int main() {
	scanf("%lld %lld", &n, &q);
	for (int i = 0; i < n; i++) {
		scanf("%lld", &arr[i]);
		dq.push_back(arr[i]);
		if (maxx <= arr[i]) {
			maxx = arr[i];
			idx = i;
		}
		noRound[i].second = arr[i];
		noRound[i + 1].first = max(noRound[i].first, noRound[i].second);
	} 
	for (int i = 0; i < idx; i++) {
		if (dq[0] < dq[1]) {
			dq.push_back(dq[0]);
			dq.pop_front();
		}
		else {
			ll temp = dq[0];
			dq.push_back(dq[1]);
			dq.pop_front();
			dq.pop_front();
			dq.push_front(temp);
		}
	}
	for (int i = 1; i < n; i++) {
		rnd.push_back(dq[i]);
	}
	for (int i = 0; i < q; i++) {
		scanf("%lld", &m);
		if (m <= idx) {
			printf("%lld %lld\n", noRound[m].first, noRound[m].second);
		}
		else {
			m -= (idx+1);
			m %= (n - 1);
			printf("%lld %lld\n", arr[idx], rnd[m]);
		}
	}
}