#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
#define MOD 1000000007
typedef long long ll;
int N;
ll dp[110][5][5][5];


// AGC ACG GAC
// A C G T 
ll solution(int pos, int b1, int b2, int b3) {
	ll &ret = dp[pos][b1][b2][b3];
	if (pos == N) {
		return 1;
	}
	if (ret != -1) return ret;
	ret = 0;
	if (b1 == 2 && b2 == 1) {
		for (int i = 1; i <= 4; i++) {
			if (i == 3) continue;
			ret += solution(pos + 1, i, b1, b2);
			ret %= MOD;
		}
	}
	else if ((b1 == 1 && b2 == 3) || (b1 == 3 && b2 == 1)) {
		for (int i = 1; i <= 4; i++) {
			if (i == 2) continue;
			ret += solution(pos + 1, i, b1, b2);
			ret %= MOD;
		}
	}
	else if ((b1 == 3 || b2 == 3) && b3 == 1) {
		for (int i = 1; i <= 4; i++) {
			if (i == 2) continue;
			ret += solution(pos + 1, i, b1, b2);
			ret %= MOD;
		}
	}
	else {
		for (int i = 1; i <= 4; i++) {
			ret += solution(pos + 1, i, b1, b2);
			ret %= MOD;
		}
	}
	return ret;
}



int main() {
	memset(dp, -1, sizeof(dp));
	cin >> N;
	ll sol = 0;

	sol = solution(0, 0, 0, 0) % MOD;
	cout << sol << endl;


}