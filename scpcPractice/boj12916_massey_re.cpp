#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<vector<ll> > matrix;

const int mod = 1e9 + 7;
int N, K;
vector<ll> sum;
vector<vector<ll> > dp;
matrix inp, temp;

matrix mul(matrix &A, matrix &B) {
	matrix ret;
	ret.assign(N, vector<ll>(N));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {

		}
	}
}
int main() {
	scanf("%d %d", &N, &K);
	inp.assign(N, vector<ll>(N));
	sum.resize(N * 3 + 1);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%lld", &inp[i][j]);
			dp[0][i] += inp[i][j];
		}
	}
	int kk = N * 3;
	temp = inp;
	for (int i = 1; i<300; i++) {
		for (int j = 0; j<n; j++) {
			for (int k = 0; k<n; k++) {
				if (a[j][k]) dp[i][k] = (dp[i - 1][j] + dp[i][k]) % mod;
			}
		}
		sum[i] = accumulate(dp[i], dp[i] + n, 0ll) % mod;
	}
}