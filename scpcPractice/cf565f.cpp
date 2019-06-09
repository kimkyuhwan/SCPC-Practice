#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, k, a, b;
int one, two, three;
ll dp[200010][10];
vector<pair<int, pair<ll, ll> > > turn[200010];

ll solution(int pos,int r)
{
	if (pos > n) return 0;
	ll &ret = dp[pos][r];
	if (ret != -1) return ret;
	ret = 0;
	for (pair<int, pair<ll, ll> > card : turn[pos + 1]) {
		if ((card.first + r) >= 10) {
			ll cost = card.second.second;
			ret = max(ret, card.second.first + cost + solution(pos + 1, (r + (card.first)) % 10));
		}
		else {
			ret = max(ret, card.second.first + solution(pos + 1, (r + (card.first)) % 10));
		}
	}
	ret = max(ret, solution(pos + 1, r));
	return ret;
}


int main() {
	memset(dp, -1, sizeof(dp));
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &k);
		vector<int> card[4];
		for (int j = 0; j < k; j++) {
			scanf("%d %d", &a, &b);
			card[a].push_back(b);
		}
		for (int j = 1; j <= 3; j++) {
			sort(card[j].rbegin(), card[j].rend());
		}
		pair<ll, ll> cost[4] = {};
		ll sum = 0;
		for (int i = 0; i < card[1].size(); i++) {
			sum += card[1][i];
			if (i <= 2) {
				cost[i + 1] = { sum,card[1][0] };
			}
			else break;
		} // 1 , 2 , 3
		  //  1 1 , 1 2
		  // 1 1 1
		if (!card[2].empty()) {
			if (cost[1].first < card[2][0]) {
				cost[1].first = card[2][0];
				cost[1].second = card[2][0];
			}
			if (!card[1].empty()) {
				if (cost[2].first < card[1][0] + card[2][0]) {
					cost[2].first = card[1][0] + card[2][0];
					cost[2].second = max(card[1][0], card[2][0]);
				}
			}
		}
		if (!card[3].empty()) {
			if (cost[1].first < card[3][0]) {
				cost[1].first = card[3][0];
				cost[1].second = card[3][0];
			}
		}
		for (int j = 1; j <= 3; j++) {
			if (cost[j].first != 0) {
				turn[i].push_back({ j,cost[j] });
			}
		}
	}
	printf("%lld\n", solution(0, 0));

}