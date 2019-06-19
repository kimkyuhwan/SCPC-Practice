#include <bits/stdc++.h>
using namespace std;
int N, x, y;
int maxx;
int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &x, &y);
		maxx = max(maxx, x + y);
	}
	printf("%d\n", maxx);
}