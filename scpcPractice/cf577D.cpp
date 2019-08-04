#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m, k, q, r, c;
const ll LINF = 1e18;
const int LEFT = 0;
const int RIGHT = 1;
const int LL = 0;
const int LR = 1;
const int RL = 2;
const int RR = 3;
vector<pair<int, int> > vec;
vector<int> cc;
vector<int> mmap[200010];
set<int> yy;
vector<int> vy;
ll ans;
ll dp[200010][4];
ll sel[200010][4];
ll lrLine[200010][2];

int main() {
	scanf("%d %d %d %d", &n, &m, &k, &q);
	for (int i = 0; i < k; i++) {
		scanf("%d %d", &r, &c);
		vec.push_back({ r,c });
		mmap[r].push_back(c);
		yy.insert(r);
	}
	sort(vec.begin(), vec.end());
	for (int i = 0; i < q; i++) {
		scanf("%d", &c);
		cc.push_back(c);
	}
	sort(cc.begin(), cc.end());

	for (auto it = yy.begin(); it != yy.end(); it++) vy.push_back(*it);
	int cnt = 1;
	for (int i : vy) {
		sort(mmap[i].begin(), mmap[i].end());
		int left = upper_bound(cc.begin(), cc.end(), mmap[i].front()) - cc.begin();
		if (left != 0) {
			left = cc[left - 1];
		}
		else {
			left = cc[left];
		}
		lrLine[cnt][0] = left;
		int right = lower_bound(cc.begin(), cc.end(), mmap[i].back()) - cc.begin();
		if (right != cc.size()) {
			right = cc[right];
		}
		else {
			right = cc[right - 1];
		}
		lrLine[cnt][1] = right;

		ll between = mmap[i].back() - mmap[i].front();
		if (cnt == vy.size()) {
			for (int i = 0; i < 4; i++) {
				sel[cnt][i] = between;
			}
		}
		else {
			sel[cnt][LL] = between + abs(left - mmap[i].front());
			sel[cnt][LR] = between + abs(right - mmap[i].front());
			sel[cnt][RL] = between + abs(mmap[i].back() - left);
			sel[cnt][RR] = between + abs(mmap[i].back() - right);
		}
		cnt++;
	}
	ans = vy.back() - 1;
	int left = 1, right = 1;
	int i = 1;
	if (vy.front() == 1) {
		dp[1][LL] = sel[1][LL] + abs(mmap[1].back() - 1);
		dp[1][LR] = sel[1][LR] + abs(mmap[1].back() - 1);
		dp[1][RL] = sel[1][RL] + abs(mmap[1].front() - 1);
		dp[1][RR] = sel[1][RR] + abs(mmap[1].front() - 1);
		left = lrLine[1][0];
		right = lrLine[1][1];
		i++;
	}
	else {
		ans += cc[0] - 1;
		left = cc[0];
		right = cc[0];
	}
	for (; i < cnt; i++) {
		dp[i][LL] = min(dp[i - 1][LR], dp[i - 1][RR]) + abs(mmap[vy[i - 1]].back() - lrLine[i - 1][RIGHT]) + sel[i][LL];
		dp[i][LR] = min(dp[i - 1][LR], dp[i - 1][RR]) + abs(mmap[vy[i - 1]].back() - lrLine[i - 1][RIGHT]) + sel[i][LR];
		dp[i][RL] = min(dp[i - 1][LL], dp[i - 1][RL]) + abs(mmap[vy[i - 1]].front() - lrLine[i - 1][LEFT]) + sel[i][RL];
		dp[i][RR] = min(dp[i - 1][LL], dp[i - 1][RL]) + abs(mmap[vy[i - 1]].front() - lrLine[i - 1][LEFT]) + sel[i][RR];
	}
	ll cost = LINF;
	for (int j = 0; j < 4; j++) {
		cost = min(cost, dp[cnt - 1][j]);
	}
	ans += cost;
	printf("%lld\n", ans);
}