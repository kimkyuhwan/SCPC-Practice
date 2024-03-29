#include <bits/stdc++.h>
using namespace std;
const int root = 0;
const int NEXT_MAX = 4;
const int NODE_MAX = 1000000;
char mmap[256];
class Aho {
private:
	int cnt;
	int next[NODE_MAX + 1][NEXT_MAX];
	int fail[NODE_MAX + 1];
	bool output[NODE_MAX + 1];
	
public:
	Aho() {
		init();
	}

	void init() {
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
			int nextIndex = mmap[*str];
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

	int isExist(char *str) {
		int current = root;
		int ret = 0;
		for (int j = 0; str[j]; j++) {
			int nextIndex = mmap[str[j]];
			while (current != root && !canGo(current, nextIndex)) {
				current = fail[current];
			}
			if (canGo(current, nextIndex)) {
				current = next[current][nextIndex];
			}
			if (output[current]) {
				ret++;
			}
		}
		return ret;
	}
};
Aho aho;
int T, N, M;
char str[1000010]="ATGGAT";
char temp[110], dna[110];
int main() {
	mmap['A'] = 0, mmap['C'] = 1, mmap['G'] = 2, mmap['T'] = 3;
	scanf("%d", &T);
	while (T--) {
		scanf(" %d %d", &N, &M);
		scanf(" %s", str);
		scanf(" %s", temp);
		aho.insert(temp);
		for (int i = 0; i < M; i++) {
			for (int j = i + 2; j <= M; j++) {
				int idx = 0;
				reverse(temp + i, temp + j);
				aho.insert(temp);
				reverse(temp + i, temp + j);
			}
		}
		aho.makeFailure();
		int ans = aho.isExist(str);
		printf("%d\n", ans);
		aho.init();
	}
}