#include <bits/stdc++.h>
using namespace std;
const int NEXT_MAX = 26;

class Trie {
private:
	Trie* next[NEXT_MAX];
	int num;

public:
	Trie() {
		fill(next, next + NEXT_MAX, nullptr);
		num = 0;
	}

	~Trie() {
		for (int i = 0; i < NEXT_MAX; i++) {
			if (next[i]) delete next[i];
		}
	}

	void insert(char *str) {
		num++;
		if (*str == '\0') {
			return;
		}
		int nextIndex = *str - 'a';
		if (!next[nextIndex]) {
			next[nextIndex] = new Trie();
		}
		next[nextIndex] -> insert(str + 1);
	}

	int solve(bool isTree = true) {
		int ret = 0;
		if (num <= 1) return 0;
		else{
			for (int i = 0; i < NEXT_MAX; i++) {
				if (next[i]) {
					if (!isTree && num!= next[i]->num) {
						ret += next[i]->num;
					}
					ret += next[i]->solve(false);
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
	while (scanf("%d",&N)!=EOF) {
		trie = new Trie();
		for (int i = 0; i < N; i++) {
			scanf(" %s", str);
			trie->insert(str);
		}
		double ans = N;
		ans+=trie->solve();
		ans /= N;
		printf("%.2lf\n", ans);
		delete trie;
	}
	return 0;
}