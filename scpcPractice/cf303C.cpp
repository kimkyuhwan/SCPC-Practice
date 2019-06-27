#include <bits/stdc++.h>
using namespace std;
int N;
typedef long long ll;
pair<ll, ll> tree[100010];
ll dp[100010];
ll w[100010];
int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%lld %lld", &tree[i].first, &tree[i].second);
		w[i] = tree[i].first;
	}
	sort(w, w + N);
	for (int i = 0; i < N; i++) {
		dp[i] = max(dp[i], 1LL);
		int next = tree[i].first + tree[i].second;
	}
}