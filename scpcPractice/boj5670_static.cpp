#include <bits/stdc++.h>
using namespace std;
const int NEXT_MAX = 26;
const int NODE_MAX = 1000000;

class Trie {
private:
	int cnt;
	int next[NODE_MAX + 1][NEXT_MAX];
	int num[NODE_MAX + 1];

public:
	Trie() {
		cnt = 1;
		memset(next, 0, sizeof(next));
		memset(num, 0, sizeof(num));
	}

	void insert(char *str, int node = 0) {
		num[node]++;
		if (*str == '\0') {
			return;
		}
		int nextIndex = *str - 'a';
		if (!next[node][nextIndex]) {
			next[node][nextIndex] = cnt++;
		}
		insert(str + 1, next[node][nextIndex]);
	}

	int solve(int node = 0) {
		int ret = 0;
		if (num[node] <= 1) return 0;
		else {
			for (int i = 0; i < NEXT_MAX; i++) {
				int nextNode = next[node][i];
				if (nextNode) {
					if (node && num[node] != num[nextNode]) {
						ret += num[nextNode];
					}
					ret += solve(next[node][i]);
				}
			}
		}
		return ret;
	}
};
int N;
char str[100];
Trie *trie;
int main() {
	while (scanf("%d", &N) != EOF) {
		trie = new Trie();
		for (int i = 0; i < N; i++) {
			scanf(" %s", str);
			trie->insert(str);
		}
		double ans = N;
		ans += trie->solve();
		ans /= N;
		printf("%.2lf\n", ans);
		delete trie;
	}
	return 0;
}