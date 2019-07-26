#include <bits/stdc++.h>
using namespace std;
int N, Q;
char str[1000010];
const int root = 0;
const int NEXT_MAX = 26;
const int NODE_MAX = 100000;
class Aho {
	int next[NODE_MAX][NEXT_MAX];
	int fail[NODE_MAX];
	bool output[NODE_MAX];
	int cnt;

public:
	void init() {
		memset(next, -1, sizeof(next));
		memset(output, 0, sizeof(output));
		memset(fail, 0, sizeof(fail));
		cnt = 1;
	}

	bool canGo(int node, int al) {
		return next[node][al] != -1;
	}
	void insert(char* key, int node = root) {
		if (*key == '\0') {
			output[node] = true;
			return;
		}
		int al = *key - 'a';
		if (!canGo(node,al)) {
			next[node][al] = cnt++;
		}
		insert(key + 1, next[node][al]);
	}

	void makeFailure() {
		queue<int> q;
		fail[root] = root;
		q.push(root);
		while (!q.empty()) {
			int node = q.front();
			q.pop();
			for (int i = 0; i < 26; i++) {
				int there = next[node][i];
				if (there == -1) continue;
				if (node == root) fail[there] = root;
				else {
					int destNode = fail[node];
					while (destNode != root && !canGo(destNode,i)) {
						destNode = fail[destNode];
					}
					if (canGo(destNode,i)) {
						destNode = next[destNode][i];
						fail[there] = destNode;
					}
				}
				if (output[fail[there]]) {
					output[there] = true;
				}
				q.push(there);
			}
		}
	}

	bool isExist(char *key) {
		int current = root;
		for (int j = 0; str[j]; j++) {
			int nextIndex = str[j] - 'a';
			while (current != root && !canGo(current,nextIndex)) {
				current = fail[current];
			}
			if (canGo(current,nextIndex)) {
				current = next[current][nextIndex];
			}
			if (output[current]) return true;
		}
		return false;
	}


}hf;

int main() {
	scanf("%d", &N);
	hf.init();
	for (int i = 0; i < N; i++) {
		scanf(" %s", str);
		hf.insert(str);
	}
	hf.makeFailure();
	scanf("%d", &Q);
	for (int i = 0; i < Q; i++) {
		scanf(" %s", str);
		bool result = hf.isExist(str);
		if (result) puts("YES");
		else puts("NO");
	}
}