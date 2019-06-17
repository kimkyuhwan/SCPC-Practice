#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
#define CHARNUM 256
vector<int> sfx, group, ng, cnt, orderToIdx;
vector<int> lcp, prevsfx, plcp;
int N, len;
char str[100010];
int dp[100010];
vector<int> fail;

bool cmp(int i, int j) {
	if (group[i] != group[j]) return group[i] < group[j];
	return group[i + len] < group[j + len];
}

vector<int> getsfx(char *s) {
	const int n = strlen(s);
	int lim = max(n + 1, CHARNUM + 1);
	sfx.clear(); group.clear(); ng.clear(); orderToIdx.clear();
	sfx.resize(n), group.resize(n + 1), ng.resize(n + 1), orderToIdx.resize(n + 1, 0);

	for (int i = 0; i<n; i++) sfx[i] = i, group[i] = s[i];

	for (int t = 1; t<n; t <<= 1) {
		cnt.clear(); cnt.resize(lim, 0);
		for (int i = 0; i<n; i++) cnt[group[min(i + t, n)]]++;
		for (int i = 1; i<lim; i++) cnt[i] += cnt[i - 1];
		for (int i = n - 1; i >= 0; i--) orderToIdx[--cnt[group[min(i + t, n)]]] = i;

		cnt.clear(); cnt.resize(lim, 0);
		for (int i = 0; i<n; i++) cnt[group[i]]++;
		for (int i = 1; i<lim; i++) cnt[i] += cnt[i - 1];
		for (int i = n - 1; i >= 0; i--) sfx[--cnt[group[orderToIdx[i]]]] = orderToIdx[i];

		auto cmp = [&](int i, int j)->bool {
			if (group[i] == group[j]) return group[i + t]<group[j + t];
			else return group[i]<group[j];
		};

		ng[sfx[0]] = 1;
		for (int i = 1; i<n; i++) {
			if (cmp(sfx[i - 1], sfx[i])) ng[sfx[i]] = ng[sfx[i - 1]] + 1;
			else ng[sfx[i]] = ng[sfx[i - 1]];
		}
		group = ng;
	}

	return sfx;
}
void getLCP() {
	lcp.resize(N + 1);
	for (int i = 0, k = 0; i<N; i++, k = max(0, k - 1)) {
		int gNum = group[i] - 1;
		if (gNum >= N - 1) continue;
		for (int j = sfx[gNum + 1]; str[i + k] == str[j + k]; k++);
		lcp[gNum] = k;
	}
}

void makeFailure() {
	fail.assign(N, 0);
	for (int i = 1, j = 0; i < N; i++) {
		while (j > 0 && str[i] != str[j]) j = fail[j - 1];
		if (str[i] == str[j]) {
			fail[i] = ++j;
		}
	}
}

int dfs(int pos) {
	int &ret = dp[pos];
	if (ret != -1) return ret;
	ret = 1;
	for (int i = pos + 1; i < N; i++) {
		if (lcp[i-1] >= N - sfx[pos])
		{
			ret += dfs(i);
			i += dfs(i) - 1;
		}
		else break;
	}
	return ret;
}


vector<pair<int, int> > ans;
int main() {
	memset(dp, -1, sizeof(dp));
	scanf(" %s", str);
	N = strlen(str);
	makeFailure();
	getsfx(str);
	getLCP();
	int current = N - 1;
	for (int i = 0; i < N; i++) {
		dfs(i);
	}
	while (current >= 0) {
		ans.push_back({ current + 1, dfs(group[N-(current+1)]-1) });
		current = fail[current]-1;
	}
	sort(ans.begin(), ans.end());
	printf("%d\n", ans.size());
	for (auto sol : ans) {
		printf("%d %d\n", sol.first, sol.second);
	}
}