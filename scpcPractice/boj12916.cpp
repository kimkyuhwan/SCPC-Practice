#include <bits/stdc++.h>
using namespace std;
#define MOD (int)(1e9+7)
typedef long long ll;
vector<vector<ll> > A[32] = {};
ll n, k;

vector<vector<ll> > getGop(const vector<vector<ll> > &A, const vector<vector<ll> > &B) {
	vector<vector<ll> > ret;
	ret.resize(n, vector<ll>(n));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++) {
				ret[i][j] += (A[i][k] * B[k][j]) % MOD;
				ret[i][j] %= MOD;
			}
		}
	return ret;
}

ll val;
ll sol;
vector<vector<ll> > ans;
vector<ll> dp;
int main() {
	scanf("%lld %lld", &n, &k);
	for (int i = 0; i < 32; i++) {
		A[i].resize(n, vector<ll>(n));
	}
	ans.resize(n, vector<ll>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%lld", &A[0][i][j]);
		}
	}
	for (int i = 1; i < 32; i++) {
		A[i] = getGop(A[i - 1], A[0]);
	}
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		ans[i][i] = 1;
	}
	while (k) {
		if (k % 2 == 1) {
			ans = getGop(ans, A[cnt]);
		}
		cnt++;
		k >>= 1;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			sol += ans[i][j];
			sol %= MOD;
		}
	}
	printf("%lld\n", sol);
}