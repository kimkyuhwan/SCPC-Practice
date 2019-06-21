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
			p.push_back({ val,i });
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
	sort(p.begin(), p.end());
	if (n == 1) {
		ans = max(val, (-val - 1));
		printf("%lld\n", ans);
		return 0;
	}
	else if (n == 2 && m.size()==1 && p.size()==1) {
		p[0].first = -p[0].first - 1;
		for (int i = 0; i < m.size(); i++) {
			arr[m[i].second] = m[i].first;
		}
		for (int i = 0; i < p.size(); i++) {
			arr[p[i].second] = p[i].first;
		}
		for (int i = 0; i < n; i++) {
			printf("%lld ", arr[i]);
		}
		return 0;
	}
	bool isPosi = (m.size() % 2) == 0;
	for (int i = 1; i < p.size(); i += 2) {
		p[i - 1].first = -p[i - 1].first - 1;
		p[i].first = -p[i].first - 1;
	}
	if (!isPosi) m[0].first = -m[0].first - 1;
	for (int i = 0; i < m.size(); i++) {
		arr[m[i].second] = m[i].first;
	}
	for (int i = 0; i < p.size(); i++) {
		arr[p[i].second] = p[i].first;
	}
	for (int i = 0; i < n; i++) {
		printf("%lld ", arr[i]);
	}
	
	return 0;
}