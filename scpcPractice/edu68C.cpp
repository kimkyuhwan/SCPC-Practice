#include <bits/stdc++.h>
using namespace std;
int q;
string s, t, p;

int cnt[26];

int main()
{
	scanf("%d", &q);
	for (int i = 0; i < q; i++) {
		memset(cnt, 0, sizeof(cnt));
		cin >> s >> t >> p;
		for (char ch : p) {
			cnt[ch - 'a']++;
		}
		int sidx = 0;
		bool ans = true;
		if (s.size() > t.size()) {
			ans = false;
		}
		else {
			int cc = 0;
			for (int tidx = 0; tidx < t.size(); tidx++) {
				int tch = t[tidx]-'a';
				if (s[sidx] == t[tidx]) {
					sidx++;
				}
				else if (cnt[tch] != 0) {
					cnt[tch]--;
					cc++;
				}
				else {
					ans = false;
				}
			}
			if (cc + s.size() > t.size()) ans = false;
		}
		if (ans) puts("YES");
		else puts("NO");
	}
}