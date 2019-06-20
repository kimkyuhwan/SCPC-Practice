#include <bits/stdc++.h>
using namespace std;
int T, N, K;
int main() {
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		scanf("%d %d", &N, &K);
		int cnt = 0;
		for (int j = 0; j < N; j++) {
			printf("%c", 'a' + cnt);
			cnt = (cnt + 1) % K;
		}
		puts("");
	}
}