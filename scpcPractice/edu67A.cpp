#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, s, t, testcase;
int main() {
	scanf("%lld", &testcase);
	for (int i = 0; i < testcase; i++) {
		scanf("%lld %lld %lld", &n, &s, &t);
		n -= min(s, t);
		n++;
		printf("%lld\n", n);
	}
}