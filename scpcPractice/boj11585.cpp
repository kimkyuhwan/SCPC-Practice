#include <bits/stdc++.h>
using namespace std;
string A, B;
int N;
vector<int> fail;

int gcd(int a, int b) {
	if (a%b == 0) return b;
	return gcd(b, a%b);
}

void makeFailure(string &M) {
	fail.assign(M.size(), 0);
	for (int i = 1, j = 0; i < M.size(); i++) {
		while (j > 0 && M[i] != M[j]) j = fail[j-1];
		if (M[i] == M[j]) fail[i] = ++j;
	}
}

int executeKMP(string &N, string &M) {
	int ret = 0;
	makeFailure(M);
	for (int i = 0, j = 0; i < N.size(); i++) {
		while (j > 0 && N[i] != M[j]) j = fail[j - 1];
		if (N[i] == M[j]) {
			j++;
			if (j == M.size()) {
				ret++;
				j = fail[j - 1];
			}
		}
		else {
			j = fail[j];
		}
	}
	return ret;
}

int main() {
	scanf("%d", &N);
	A.resize(N * 2), B.resize(N);
	for (int i = 0; i < N; i++) {
		scanf(" %c", &A[i]);
		A[N + i] = A[i];
	}
	for (int i = 0; i < N; i++) {
		scanf(" %c", &B[i]);
	}
	A.pop_back();
	int ans = executeKMP(A, B);
	int g = gcd(N, ans);
	printf("%d/%d\n", ans / g, N / g);
}