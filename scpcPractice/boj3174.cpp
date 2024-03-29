#include <bits/stdc++.h>
using namespace std;
#define MOD 1337377
#define INF 1e9
const int root = 0;
const int NEXT_MAX = 26;
const int NODE_MAX = 400010;
typedef long long ll;
int N, K;

char str[300010];
char temp[110];
class Aho {
private:
	int cnt;
	int next[NODE_MAX + 1][NEXT_MAX];
	int fail[NODE_MAX + 1];
	ll output[NODE_MAX + 1];
	ll dp[300010];

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
			output[node]++;
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
				q.push(nextNode);
			}
		}
	}

	int isExist(char *str) {
		int current = root;
		int ret = 0;
		for (int j = 0; str[j]; j++) {
			int nextIndex = str[j] - 'a';
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

	ll solution(int node = root) {
		int m = strlen(str);
		dp[m] = 1;

		for (int i = m - 1; i >= 0; --i) {
			int t = root;
			for (int j = i; j < m; ++j) {
				t = next[t][str[j] - 'a'];
				if (t == 0) break;
				if (output[t]) dp[i] = (dp[i] + dp[j + 1]) % MOD;
			}
			dp[i] %= MOD;
		}
		return dp[0];
	}

};

Aho aho;

int main() {
	scanf("%s", str);
	scanf(" %d", &N);
	for (int i = 1; i <= N; i++) {
		scanf(" %s", temp);
		aho.insert(temp);
	}
	aho.makeFailure();
	ll ans = aho.solution(0);

	printf("%lld\n", ans);
}