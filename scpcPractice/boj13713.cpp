#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
#define CHARNUM 256
vector<int> sfx, g, ng, cnt, orderToIdx;
vector<int> lcp,	 prevsfx, plcp;
char str[2000010];
int N, M, K, val;
int dp[200010];
////get Suffix Array O(NlogN) using counting sort.
vector<int> getsfx(const string &s) {
	const int n = s.size();
	int lim = max(n + 1, CHARNUM + 1);
	sfx.clear(); g.clear(); ng.clear(); orderToIdx.clear();
	sfx.resize(n), g.resize(n + 1), ng.resize(n + 1), orderToIdx.resize(n + 1, 0);

	for (int i = 0; i<n; i++) sfx[i] = i, g[i] = s[i];

	for (int t = 1; t<n; t <<= 1) {
		cnt.clear(); cnt.resize(lim, 0);
		for (int i = 0; i<n; i++) cnt[g[min(i + t, n)]]++;
		for (int i = 1; i<lim; i++) cnt[i] += cnt[i - 1];
		for (int i = n - 1; i >= 0; i--) orderToIdx[--cnt[g[min(i + t, n)]]] = i;

		cnt.clear(); cnt.resize(lim, 0);
		for (int i = 0; i<n; i++) cnt[g[i]]++;
		for (int i = 1; i<lim; i++) cnt[i] += cnt[i - 1];
		for (int i = n - 1; i >= 0; i--) sfx[--cnt[g[orderToIdx[i]]]] = orderToIdx[i];

		auto cmp = [&](int i, int j)->bool {
			if (g[i] == g[j]) return g[i + t]<g[j + t];
			else return g[i]<g[j];
		};

		ng[sfx[0]] = 1;
		for (int i = 1; i<n; i++) {
			if (cmp(sfx[i - 1], sfx[i])) ng[sfx[i]] = ng[sfx[i - 1]] + 1;
			else ng[sfx[i]] = ng[sfx[i - 1]];
		}
		g = ng;
	}

	return sfx;
}
void getLCP() {
	lcp.resize(N + 1);
	for (int i = 0, k = 0; i<N; i++, k = max(0, k - 1)) {
		int gNum = g[i] - 1;
		if (gNum >= N - 1) continue;
		for (int j = sfx[gNum + 1]; str[i + k] == str[j + k]; k++);
		lcp[gNum] = k;
	}
}

int solution(int pos) {
	int &ret = dp[pos];
	if (ret != -1) return ret;
	ret = 0;
	for (int i = pos+1; i < N; i++) {
		if (lcp[i] >= N - sfx[pos]) {
			ret += solution(i);
		}

	}
	return ret;
}

int main() {
	memset(dp, -1, sizeof(dp));
	scanf("%s", str);
	N = strlen(str);
	vector<int> ans = getsfx(str);
	getLCP();
	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		scanf("%d", &val);
		printf("%d\n", lcp[val+K]);
	}
}