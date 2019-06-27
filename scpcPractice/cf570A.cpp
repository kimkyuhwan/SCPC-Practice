#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N;

ll getSum(ll A) {
	ll sum = 0;
	while (A) {
		sum += A % 10;
		A /= 10;
	}
	return sum;
}

int main()
{
	scanf("%lld", &N);
	while (getSum(N) % 4 != 0) {
		N++;
	}
	printf("%d", N);
}