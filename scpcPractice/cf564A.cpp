#include <bits/stdc++.h>
using namespace std;
int x, y, z;
int main() {
	scanf("%d %d %d", &x, &y, &z);
	int ans = x - y;
	if (ans < 0) {
		if (abs(ans) <= z) puts("?");
		else puts("-");
	}
	else if (ans > 0) {
		if (abs(ans) <= z) puts("?");
		else puts("+");
	}
	else {
		if (z > 0) puts("?");
		else puts("0");
	}
}