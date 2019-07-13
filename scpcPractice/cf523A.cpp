#include <bits/stdc++.h>
using namespace std;
int N, S, ans;
int main()
{
	scanf("%d %d", &N, &S);
	ans = S / N;
	if (S%N != 0) {
		ans++;
	}
	printf("%d\n", ans);
}