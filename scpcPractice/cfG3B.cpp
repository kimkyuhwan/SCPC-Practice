#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N, M, K, ta, tb;
ll A[200010], B[200010];

int main() {
	scanf("%lld %lld %lld %lld %lld", &N, &M, &ta,&tb,&K);
	for (int i = 0; i < N; i++) {
		scanf("%lld", &A[i]);
	}
	for (int i = 0; i < M; i++) {
		scanf("%lld", &B[i]);
	}
	ll sol=0;

	if (K >= N || K >= M) {
		puts("-1");
		return 0;
	}
	for (int i = 0; i <= K; i++) {
		int arrivalB = A[i] + ta;
		int startJ = upper_bound(B, B + M, arrivalB)-B;
		if (B[startJ-1] == arrivalB) {
			startJ--;
		}
		if (K - i > 0) {
			startJ += (K - i);
		}
		if (startJ >= M) {
			puts("-1");
			return 0;
		}
		else {
			sol = max(sol, B[startJ] + tb);
		}
	}
	printf("%lld\n", sol);
}