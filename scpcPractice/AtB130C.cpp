#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll W, H, x, y, mul;
double ans;
int main() {
	scanf("%lld %lld %lld %lld", &W, &H,&x,&y);
	double ans = (double)(W*H) / 2;

	if (W == x*2 && H == y*2) {
		mul = 1;
	}
	printf("%.6lf %d\n", ans, mul);
}