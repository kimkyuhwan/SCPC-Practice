#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) {
	if (a < b) {
		swap(a, b);
	}
	if (a%b == 0) return b;
	return gcd(b, a%b);
}


ll lcm(ll a, ll b) {
	return a*b/ gcd(a,b);
}

int N, T;
ll val;
int main() {
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		vector<ll> vec, temp;
		scanf("%d", &N);
		for (int j = 0; j < N; j++) {
			scanf("%lld", &val);
			vec.push_back(val);
		}
		sort(vec.begin(),vec.end());
		ll ans = vec[0] * vec[N - 1];
		for (ll j = 2; j <= sqrt(ans); j++) {
			if (j*j == ans) {
				temp.push_back(j);
			}
			else if (ans%j == 0) {
				temp.push_back(j);
				temp.push_back(ans/j);
			}	
		}
		sort(temp.begin(), temp.end());
		if (vec == temp) {
			printf("%lld\n", ans);
		}
		else {
			puts("-1");
		}
	}
}