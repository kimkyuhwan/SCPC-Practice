#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<int> > matrix;
typedef long long ll;
#define MOD 1000
int N;
ll B;
matrix arr[64];


matrix multiple(const matrix &A, const  matrix &B) {
	matrix ret;
	ret.resize(N, vector<int>(N));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				ret[i][j] = (ret[i][j] + A[i][k] * B[k][j])%MOD;
			}
		}
	}
	return ret;
}




void initArray() {
	for (int n = 1; n < 64; n++) {
		arr[n] = multiple(arr[n - 1], arr[n - 1]);
	}
}


int main() {
	scanf("%d %lld", &N, &B);
	for (int i = 0; i < 64; i++) arr[i].resize(N, vector<int>(N));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf(" %d", &arr[0][i][j]);
		}
	}
	initArray();
	int cnt = 0;
	matrix ans;
	ans.resize(N, vector<int>(N));
	for (int i = 0; i < N; i++) ans[i][i] = 1;
	while (B) {
		if (B % 2 == 1) {
			ans = multiple(ans, arr[cnt]);
		}
		cnt++;
		B >>= 1;
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", ans[i][j]);
		}
		puts("");
	}
}