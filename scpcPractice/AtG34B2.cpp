	#include <bits/stdc++.h>
	using namespace std;
	typedef long long ll;
	string str;
	ll N;

	ll solution() {
		ll sol = 0;
		ll A = 0;
		for (int i=0; i <N-1; i++) {
			if (str[i] == 'A') {
				A++;
			}
			else if (str[i] == 'B' && str[i+1] == 'C') {
				sol += A;
				i++;
			}
			else {
				A = 0;
			}
		}
		return sol;
	}

	int main() {
		cin >> str;
		N = str.size();

		ll ans = solution();
		cout << ans << endl;
	}