#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll s, a, b, c;
ll ans;
ll used, newC;
int T;
int main() {
	cin >> T;
	while (T--) {
		ans = 0;
		cin >> s >> a >> b >> c;
		ll candy = s/c;	
		ans = (s / (a*c))*b + candy;
		cout << ans << endl;
	}
}