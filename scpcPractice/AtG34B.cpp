#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
string str;
ll N;

ll solution(int pos, int state,int cnt) {
	ll ret = 0;
	if (pos == N) return 0;
	if (state == 0) {
		if (pos < N - 2) {
			if (str[pos] == 'A' && str[pos + 1] == 'B' && str[pos + 2] == 'C') {
				ret = (1 + solution(pos + 3, 1, 1));
			}
			else if (str[pos] == 'A') {
				ret = solution(pos + 1, 1, 1);
			}
			else {
				ret = solution(pos + 1, 0, 0);
			}
		}
		else {
			ret = solution(pos + 1, 0, 0);
		}
	}
	else if (state == 1) {
		if (pos < N - 1) {
			if (str[pos] == 'B' && str[pos + 1] == 'C') {
				return ret = (cnt + solution(pos + 2,1, cnt));
			}
		}
		if (str[pos] == 'A') {
			ret = solution(pos + 1, 1, cnt + 1);
		}
		else {
			ret = solution(pos + 1, 0, 0);
		}
	}
	return ret;
}

int main() {
	cin >> str;
	N = str.size();

	ll ans = solution(0, 0, 0);
	printf("%lld\n", ans);
}