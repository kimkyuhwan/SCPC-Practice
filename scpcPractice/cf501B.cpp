#include <bits/stdc++.h>
using namespace std;
int n, m, cnt;
char s[110], t[110];
void swap(char *a, char *b) {
	char temp = *a;
	*a = *b;
	*b = temp;
}
vector<int> ans;
int idx[26];
vector<int> ss[26], tt[26];
int sz[26];
void init() {
	for (int i = 0; i < 26; i++) {
		ss[i].clear();
		tt[i].clear();
	}
	for (int i = 0; i < n; i++) {
		ss[s[i] - 'a'].push_back(i);
		
	}
	for (int i = 0; i < n; i++) {
		tt[t[i] - 'a'].push_back(i);
		
	}
}

int main()
{
	scanf("%d", &n);
	scanf(" %s", s);
	
	scanf(" %s", t);
	
	for (int i = 0; i < n; i++) {
		sz[s[i] - 'a']++;
		sz[t[i] - 'a']--;
	}
	for (int i = 0; i < 26; i++) {
		if (sz[i] != 0) {
			puts("-1");
			return 0;
		}
	}
	while (strcmp(s, t)) {
		memset(idx, 0, sizeof(idx));
		for (int i = 0; i < n; i++) {
			int here = s[i] - 'a';
			if (t[i] == s[i]) {
				idx[here]++;
				continue;
			}
			init();
			if (tt[here].size() <= idx[here] || ss[here].size() <= idx[here]) {
				puts("-1");
				return 0;
			}
			int l = ss[here][idx[here]];
			int r = tt[here][idx[here]];
			if (l < r) {
				for (int j = l; j < r; j++) {
					swap(s[j], s[j + 1]);
					ans.push_back(j + 1);
				}
			}
			else {
				for (int j = l; j > r; j--) {
					swap(s[j - 1], s[j]);
					ans.push_back(j);
				}
			}

		}
	}
	printf("%d\n", ans.size());
	for (int i : ans) {
		printf("%d ", i);
	}

}