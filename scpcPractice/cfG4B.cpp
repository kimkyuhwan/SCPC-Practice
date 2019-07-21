#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
char s[1000010];
ll psum[1000010];
ll ans;
int main() {
	scanf(" %s", s);
	int len = strlen(s);
	int cnt = 0;
	for (int i = 0; i < len; i++) {
		psum[i+1] = psum[i];
		if (s[i] == 'v') {
			cnt++;
			if (cnt >= 2) {
				psum[i+1]++;
			}
		}
		else {
			cnt = 0;
		}
	}
	for (int i = 0; i < len; i++) {
		if (s[i] == 'o') {
			ans += psum[i] * (psum[len] - psum[i + 1]);
		}
	}
	printf("%lld\n", ans);
}