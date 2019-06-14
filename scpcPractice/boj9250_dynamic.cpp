#include <bits/stdc++.h>
using namespace std;
const int root = 0;
const int NEXT_MAX = 26;
const int NODE_MAX = 100000;
class Aho {
private:
	int cnt;
	int next[NODE_MAX + 1][NEXT_MAX];
	int fail[NODE_MAX + 1];
	bool output[NODE_MAX + 1];
	
public:
	Aho() {
		cnt = 1;
		memset(next, 0, sizeof(next));
		memset(output, 0, sizeof(output));
		memset(fail, 0, sizeof(fail));
	}

	bool canGo(int node, int nextIndex) {
		return next[node][nextIndex] != 0;
	}

	void insert(char *str, int node = root) {
		if (*str == '\0') {
			output[node] = true;
		}
		else {
			int nextIndex = *str - 'a';
			if (!canGo(node, nextIndex)) {
				next[node][nextIndex] = cnt++;
			}
			insert(str + 1, next[node][nextIndex]);
		}
	}

	void makeFailure() {
		queue<int> q;
		q.push(root);
		fail[root] = root;
		while (!q.empty()) {
			int node = q.front();
			q.pop();
			for (int i = 0; i < NEXT_MAX; i++) {
				int nextNode = next[node][i];
				if (!nextNode) continue;
				if (node == root) {
					fail[nextNode] = root;
				}
				else {
					int destNode = fail[node];
					while (destNode != root && !next[destNode][i]) {
						destNode = fail[destNode];
					}
					if (next[destNode][i]) {
						destNode = next[destNode][i];
						fail[nextNode] = destNode;
					}
				}
				if (output[fail[nextNode]]) {
					output[nextNode] = true;
				}
				q.push(nextNode);
			}
		}
	}

	bool isExist(char *str) {
		int current = root;
		for (int j = 0; str[j]; j++) {
			int nextIndex = str[j] - 'a';
			while (current != root && !canGo(current, nextIndex)) {
				current = fail[current];
			}
			if (canGo(current, nextIndex)) {
				current = next[current][nextIndex];
			}
			if (output[current]) {
				return true;
			}
		}
		return false;
	}
};
Aho aho;
int N, M;
char str[10010];
int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf(" %s", str);
		aho.insert(str);
	}
	aho.makeFailure();
	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		scanf(" %s", str);
		bool ans = aho.isExist(str);
		if (ans) puts("YES");
		else puts("NO");
	}
}