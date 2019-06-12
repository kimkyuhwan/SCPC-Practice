#include <bits/stdc++.h>
using namespace std;
#define NEXT_MAX 10

class Trie {
private:
	Trie *next[NEXT_MAX];
	bool isNode;
	bool hasChild;

public:
	Trie() {
		fill(next, next + NEXT_MAX, nullptr);
		isNode = hasChild = false;
	}
	~Trie() {
		for (int i = 0; i < NEXT_MAX; i++) {
			if (next[i]) delete next[i];
		}
	}
	bool insert(char *key) {
		if (*key == '\0') {
			isNode = true;
			return !hasChild;
		}
		else {
			int nextIndex = *key - '0';
			if (!next[nextIndex]) {
				next[nextIndex] = new Trie();
			}
			hasChild = true;
			return !isNode && next[nextIndex]->insert(key + 1);
		}
	}
};
int TC, N;
char str[30];

int main() {
	scanf("%d", &TC);
	for (int i = 0; i < TC; i++) {
		Trie *root = new Trie();
		scanf("%d", &N);
		bool result = true;
		for (int j = 0; j < N; j++) {
			scanf(" %s", str);
			if (result) {
				result = root->insert(str);
			}
		}
		if (result) puts("YES");
		else puts("NO");
		delete root;
	}
	return 0;
}