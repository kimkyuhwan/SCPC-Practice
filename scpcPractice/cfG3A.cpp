#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll A, B, C;
int main() {
	scanf("%lld %lld %lld", &A, &B, &C);
	ll sol = C*2;
	sol += min(A, B)*2;
	if (A != B) {
		sol++;
	}
	printf("%lld\n", sol);
}