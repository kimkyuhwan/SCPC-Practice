#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
const int root = 0;
const int NEXT_MAX = 3;
const int NODE_MAX = 1010;

int N, K;
class Aho {
private:
	int cnt;
	int next[NODE_MAX + 1][NEXT_MAX];
	int fail[NODE_MAX + 1];
	int output[NODE_MAX + 1];
	int	dp[1010][NODE_MAX+1];

public:
	Aho() {
		init();
	}

	void init() {
		cnt = 1;
		memset(next, 0, sizeof(next));
		memset(output, 0, sizeof(output));
		memset(fail, 0, sizeof(fail));
		memset(dp, -1, sizeof(dp));
	}

	bool canGo(int node, int nextIndex) {
		return next[node][nextIndex] != 0;
	}

	void insert(char *str, int node = root) {
		if (*str == '\0') {
			output[node]++;
		}
		else {
			int nextIndex = *str - 'A';
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
					output[nextNode]+=output[fail[nextNode]];
				}
				q.push(nextNode);
			}
		}
	}

	int isExist(char *str) {
		int current = root;
		int ret = 0;
		for (int j = 0; str[j]; j++) {
			int nextIndex = str[j]-'A';
			while (current != root && !canGo(current, nextIndex)) {
				current = fail[current];
			}
			if (canGo(current, nextIndex)) {
				current = next[current][nextIndex];
			}
			ret += output[current];
		}
		return ret;
	}

	int solution(int pos, int node) {
		if (pos == K) return 0;
		int &ret = dp[pos][node];
		if (ret != -1) return ret;
		ret = 0;
		int nextNode = node;
		int cnt=0;
		int state = 0;
		do {
			for (int i = 0; i < 3; i++) {
				if (state & (1<<i)) continue;
				if (canGo(nextNode, i)) {
					int thereNode = next[nextNode][i];
					state |= (1 << i);
					ret = max(ret, solution(pos + 1, thereNode) + output[thereNode]);
				}
			}
			nextNode = fail[nextNode];
			if (nextNode == root) {
				cnt++;
			}
			if (state == ((1 << NEXT_MAX) - 1)) break;
			if (cnt == 2) break;

		} while (true);
		return ret;
	}

};


Aho aho;

char str[21][21];
int val[21];


int main() {
	scanf("%d %d", &N, &K);
	for (int i = 1; i <= N; i++) {
		scanf("%s", str[i]);
		aho.insert(str[i]);
	}
	aho.makeFailure();
	int ans = aho.solution(0, 0);
	printf("%d\n", ans);
}