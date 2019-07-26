#include <bits/stdc++.h>
using namespace std;
const int NEXT_MAX = 10;
const int NODE_MAX = 100010;
class Trie {
private :
	int cnt;
	int next[NODE_MAX][NEXT_MAX];
	bool hasChild[NODE_MAX];
	bool isNode[NODE_MAX];

public:
	void init() {
		cnt = 1;
		memset(next, -1, sizeof(next));
		memset(hasChild, 0, sizeof(hasChild));
		memset(isNode, 0, sizeof(isNode));
	}

	bool insert(char *key, int node = 0) {
		if (*key == '\0') {
			isNode[node] = true;
			return !hasChild[node];
		}
		int num = *key - '0';
		hasChild[node] = true;
		if (next[node][num] == -1) {
			next[node][num] = cnt++;
		}
		return !isNode[node] && insert(key + 1, next[node][num]);
	}
}tr;
int t, n;
char str[110];
int main()
{
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		tr.init();
		bool ans = true;
		for (int i = 0; i < n; i++) {
			scanf(" %s", str);
			bool result = tr.insert(str);
			if (!result) ans = result;
		}
		if (ans) puts("YES");
		else puts("NO");
	}
}