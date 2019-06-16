#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000009
#define INF 1e9
const int root = 0;
const int NEXT_MAX = 26;
const int NODE_MAX = 310;
typedef long long ll;
int N, C, L;

char temp[110];
class Aho {
private:
	int cnt;
	int num;
	int next[NODE_MAX + 1][NEXT_MAX];
	int fail[NODE_MAX + 1];
	ll output[NODE_MAX + 1];
	ll dp[10][52][NODE_MAX][64];

public:
	Aho() {
		init();
	}

	void init() {
		cnt = 1;
		num = 0;
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
			output[node] = (1<<num);
			num++;
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
						output[nextNode] |= output[fail[nextNode]];
					}
				}
				q.push(nextNode);
			}
		}
	}

	int getDiffernce(int src, int dst) {
		int state = (src ^ dst);
		int ret = 0;
		state &= ~(src);
		while (state) {
			if (state % 2) {
				ret++;
			}
			state >>= 1;
		}
		return ret;
	}

	ll solution(int remainC, int pos, int node,int state) {
		if (remainC < 0) return 0;
		if (pos == L) {
			if (remainC > 0) return 0;
			else if (remainC == 0) return 1;
		}
		ll &ret = dp[remainC][pos][node][state];
		if (ret != -1) return ret;
		ret = 0; 
		for (int i = 0; i < 26; i++) {
			int temp = node;
			while (true) {
				int nextNode = next[temp][i];
				if (nextNode) {
					if (output[nextNode] && !((state & output[nextNode]) == output[nextNode])) {
						ret = (ret + solution(remainC - getDiffernce(state, output[nextNode]), pos + 1, nextNode, state | output[nextNode])) % MOD;
						break;
					}
					else {
						ret = (ret + solution(remainC, pos + 1, nextNode, state)) % MOD;
						break;
					}
				}
				else if(temp==root){
					ret = (ret + solution(remainC, pos + 1, root, state)) % MOD;
					break;
				}
				temp = fail[temp];
			}
		}
		return ret;
	}

};

Aho aho;
int main() {
	scanf("%d %d %d", &N,&C,&L);
	for (int i = 1; i <= N; i++) {
		scanf(" %s", temp);
		aho.insert(temp);
	}
	aho.makeFailure();
	ll ans = aho.solution(C, 0, 0, 0);
	printf("%lld\n", ans);
}