#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
map<ll, ll> aa;
vector<ll> vec;
ll n, k;
ll ans;
vector<ll> num;
vector<ll> nextCnt;
int main()
{
	scanf("%lld %lld", &n, &k);
	vec.resize(n);
	for (int i = 0; i < n; i++) {
		scanf("%lld", &vec[i]);
	}
	sort(vec.begin(), vec.end());
	for (int i = n / 2; i < n; i++) {
		aa[vec[i]]++;
	}
	int ccnt = 0;
	nextCnt.resize(aa.size());
	for (auto it = aa.begin(); it != aa.end(); it++) {
		num.push_back(it->first);
		if (ccnt > 0) {
			nextCnt[ccnt] = nextCnt[ccnt - 1];
		}
		nextCnt[ccnt] += it->second;
		ccnt++;
	}
	ans = -1;
	for (int i = 0; i < num.size() - 1; i++) {
		ll nextDifference = num[i + 1] - num[i];
		ll cost = 1LL * nextCnt[i] * nextDifference;
		if (cost > k) {
			ll diff = k / nextCnt[i];
			ans = max(ans, num[i] + diff);
			break;
		}
		else {
			k -= cost;
		}
	}
	if (ans == -1) {
		int l = nextCnt.size() - 1;
		ans = num[l] + k / (nextCnt[l]);
	}
	printf("%lld\n", ans);
}