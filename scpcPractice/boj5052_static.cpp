#include <bits/stdc++.h>
using namespace std;
#define NEXT_MAX 10
#define CHAR_MAX 100000

class Trie {
private:
	int cnt;
	int next[CHAR_MAX+1][NEXT_MAX];
	bool isNode[CHAR_MAX+1];
	bool hasChild[CHAR_MAX+1];

public:
	Trie() {
		cnt = 1;
		memset(next, 0, sizeof(next));
		memset(isNode, 0, sizeof(isNode));
		memset(hasChild, 0, sizeof(hasChild));
	}
	bool insert(char *key, int node=0) {
		if (*key == '\0') {
			isNode[node] = true;
			return !hasChild[node];
		}
		else {
			int nextIndex = *key - '0';
			if (!next[node][nextIndex]) {
				next[node][nextIndex] = cnt++;
			}
			hasChild[node] = true;
			return !isNode[node] && insert(key + 1,next[node][nextIndex]);
		}
	}
};
int TC, N;
char str[30];
Trie *trie;

int main() {
	scanf("%d", &TC);
	for (int i = 0; i < TC; i++) {
		scanf("%d", &N);
		bool result = true;
		trie = new Trie();
		for (int j = 0; j < N; j++) {
			scanf(" %s", str);
			if (result) {
				result = trie->insert(str);
			}
		}
		if (result) puts("YES");
		else puts("NO");
		delete trie;
	}
	return 0;
}