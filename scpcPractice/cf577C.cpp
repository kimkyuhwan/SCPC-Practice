#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
map<int, int> aa;
vector<int> vec;
int n, k, ans;
vector<int> num;
int main()
{
	scanf("%d %d", &n, &k);
	vec.resize(n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &vec[i]);
	}
	sort(vec.begin(), vec.end());
	for (int i = n / 2; i < n; i++) {
		aa[vec[i]]++;
	}
	for (auto it = aa.begin(); it != aa.end(); it++) {
		num.push_back(it->first);
	}
	ans = num[0];
	for (int i = 0; i < num.size()-1; i++) {
		int nextDifference = num[i + 1] - num[i];
		int nextCnt = aa[num[i]];
		ll cost = 1LL * nextCnt * nextDifference;
		if (cost > k) {
			int diff = k / nextCnt;
			ans = max(ans, num[i] + diff);
			k = 0;
		}
		else {
			ans = max(ans, num[i + 1]);
			k -= cost;
		}
	}
	if (k != 0) {
		ans += k / ((n / 2)+1);
	}
	printf("%d\n", ans);
}