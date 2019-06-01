#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
int N, M, C, K;
vector<int> mo[21];
int dp[210][21];
int solution(int total, int pos) {
	if (total > M) return -1;
	if (pos == C) {
		return total;
	}
	int &ret = dp[total][pos];
	if (ret != -1) return ret;
	ret = 0;
	for (int cost : mo[pos]) {
		ret=max(ret,solution(total + cost, pos + 1));
	}
	return ret;
}



int main() {
	scanf("%d", &N);
	while (N--) {
		memset(dp, -1, sizeof(dp));
		scanf("%d %d", &M, &C);
		for (int i = 0; i < C; i++) {
			scanf("%d", &K);
			mo[i].clear();
			mo[i].resize(K);
			for (int j = 0; j < K; j++) {
				scanf("%d", &mo[i][j]);
			}
		}
		int sol = solution(0, 0);
		if (sol <= 0) {
			puts("no solution");
		}
		else {
			printf("%d\n", sol);
		}
	}
}