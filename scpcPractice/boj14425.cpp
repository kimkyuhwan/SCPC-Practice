#include <bits/stdc++.h>
using namespace std;
const int NEXT_MAX = 26;
const int NODE_MAX = 5000010;
const int root = 0;
int N, M;
char str[510];

class Trie {
private:
	bool output[NODE_MAX + 1];
	int next[NODE_MAX][NEXT_MAX];
	int cnt;

public:
	Trie() {
		init();
	}
	void init() {
		memset(output, 0, sizeof(output));
		memset(next, 0, sizeof(output));
		cnt = 1;
	}
	
	void insert(char *str, int node= root) {
		if (*str == '\0') {
			output[node] = true;
		}
		else {
			int nextIndex = *str - 'a';
			if (next[node][nextIndex]==0) {
				next[node][nextIndex] = cnt++;
			}
			insert(str + 1, next[node][nextIndex]);
		}
	}
	bool isExist(char *str, int node = root) {
		if (*str == '\0') {
			return output[node];
		}
		int nextIndex = *str - 'a';
		if (next[node][nextIndex]) {
			return isExist(str + 1, next[node][nextIndex]);
		}
		return false;
	}

};


Trie trie;
int ans;
int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		scanf("%s", str);
		trie.insert(str);
	}
	for (int i = 0; i < M; i++) {
		scanf("%s", str);
		bool flag = trie.isExist(str);
		ans += flag;
	}
	printf("%d\n", ans);
}