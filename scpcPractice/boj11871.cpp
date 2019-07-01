#include <bits/stdc++.h>
using namespace std;
int N, val, x;
int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &val);
		x ^= val;
	}
	if (x == 0) puts("cubelover");
	else puts("koosaga");
}