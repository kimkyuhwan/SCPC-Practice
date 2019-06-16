#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll x, y, z;
ll sol, minn;
int main() {
	scanf("%lld %lld %lld", &x, &y, &z);
	sol += (x / z) + (y / z);
	x %= z;
	y %= z;
	if (x + y >= z) {
		sol += (x + y) / z;
		minn = min(z - x, z - y);
	}
	printf("%lld %lld\n", sol, minn);
}