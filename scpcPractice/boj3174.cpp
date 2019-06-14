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
	ll sum[300010];

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
					if (output[fail[nextNode]]) {
						output[nextNode] += output[fail[nextNode]];
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
		ll ret = 1;
		int cnt = 0;
		ll sum = 0;
		int sz = strlen(str);
		for(int pos=0;pos<sz;pos++) {
			int hereChar = str[pos] - 'a';
			int nextNode = next[node][hereChar];
			if (nextNode) {
				sum = max(sum, output[nextNode]);
				node = nextNode;
				if (pos == sz - 1) {
					ret *= sum;
				}
			}
			else {

				ret *= sum;
				ret %= MOD;
				sum = 0;
				while (next[node][hereChar]==0) {
					node = fail[node];
				}
				nextNode = next[node][hereChar];
				sum += output[nextNode];
				node = nextNode;
				sum %= MOD;
			}
		}
		return ret;
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