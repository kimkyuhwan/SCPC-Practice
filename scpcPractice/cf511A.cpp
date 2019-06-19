#include <bits/stdc++.h>
using namespace std;
int N, A, B, C;
int main() {
	scanf("%d", &N);
	A = B = 1;
	for (C = N - 2; C % 3 == 0 && C >= 0; C--) {
		B++;
	}

	printf("%d %d %d\n", A,B,C);
}