#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define INF
int n;
vector<pair<ll, ll> > m, p, zero;
ll val;
ll ans;
bool isChange[100010];
ll arr[100010];
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%lld", &val);
		arr[i] = val;
		if (val > 0) {
			m.push_back({ -val-1,i });
		}
		else if (val == 0) {
			m.push_back({ -1,i });
			arr[i] = -1;
		}
		else {
			m.push_back({ val,i });
		}
	}
	sort(m.begin(), m.end());
	if (n == 1) {
		ans = max(val, (-val - 1));
		printf("%lld\n", ans);
		return 0;
	}
	bool isPosi = (m.size() % 2) == 0;
	if (!isPosi) m[0].first = -m[0].first - 1;
	for (int i = 0; i < m.size(); i++) {
		arr[m[i].second] = m[i].first;
	}
	for (int i = 0; i < n; i++) {
		printf("%lld ", arr[i]);
	}
	
	return 0;
}