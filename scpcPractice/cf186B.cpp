#include <bits/stdc++.h>
using namespace std;
char s[100010];
int M, A, B, N;
int psum[100010];

void init() {
	for (int i = 1; i <= N; i++) {
		psum[i] = psum[i-1] + (s[i - 1] == s[i]);
	}
}

int main() {
	scanf("%s", s);
	scanf("%d", &M);
	N = strlen(s);
	init();
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &A, &B);
		int ans = psum[B-1] - psum[A-1];
		printf("%d\n", ans);
	}
}