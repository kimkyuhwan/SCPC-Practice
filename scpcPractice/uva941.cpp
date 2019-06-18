#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int T;
char str[30], ans[30];
ll dp[30], N;

void initTable() {
	dp[0] = 1;
	for (int i = 1; i <= 20; i++) {
		dp[i] = dp[i - 1] * i;
	}
}

ll getIndex() {
	int len = strlen(str);
	ll ret = 0;
	for (int i = 0; i < len; i++) {
		int cnt = 0;
		for(int j=i+1;j<len;j++){
			if (str[i] > str[j]) {
				cnt++;
			}
		}
		ret += cnt*dp[len - 1 - i];
	}
	return ret;
}

void solve(ll num, ll len) {
	sort(str, str + len);
	vector<bool> used(len);
	for (int i = len - 1, j=0; i >= 0; i--,j++) {
		char temp;
		ll cnt = num / dp[i];
		num %= dp[i];
		int idx = 0;
		for (int k = 0; k < len && cnt >=0; k++) {
			if (used[k]) continue;
			cnt--;
			idx = k;
			ans[j] = str[idx];
		}
		used[idx] = true;
	}
	ans[len] = '\0';
}


int main() {
	initTable();
	scanf("%d", &T);
	while (T--) {
		scanf(" %s", str);
		scanf("%lld", &N);
		ll len = strlen(str);
		ll idx = getIndex();
		idx = N;
		idx %= dp[len];
		solve(idx, len);
		printf("%s\n", ans);
	}
}