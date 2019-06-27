#include <bits/stdc++.h>
using namespace std;
char s[100010];
int N, A, B;
int dp[100010][3];

int solution(int pos, int state) {
	if (state == 3) return 1;
	if (pos >= N) return 0;
	int &ret = dp[pos][state];
	if (ret != -1) return ret;
	ret = 0;
	ret += solution(pos + 1, state);
	if (s[pos] == 'A' && s[pos + 1] == 'B' && state != 1) ret += solution(pos + 2, state | 1);
	if (s[pos] == 'B' && s[pos + 1] == 'A' && state != 2) ret += solution(pos + 2, state | 2);
	return ret;
}

int main() {
	memset(dp, -1, sizeof(dp));
	scanf(" %s", s);
	N = strlen(s);
	int ans = solution(0, 0);
	if (ans) { puts("YES"); }
	else { puts("NO"); }
}