#include <bits/stdc++.h>
using namespace std;
int T, N, M;
pair<int, int> S[26], E[26];
bool isVisited[26];
char r[2010][2010], sim[2010][2010];
int main()
{
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		scanf("%d %d", &N, &M);
		memset(S, 0, sizeof(S));
		memset(E, 0, sizeof(E));
		memset(isVisited, 0, sizeof(isVisited));
		int lastAl = -1;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				scanf(" %c", &r[i][j]);
				if (r[i][j] == '.') continue;
				int idx = r[i][j] - 'a';
				if (!isVisited[idx]) {
					S[idx].first = i;
					S[idx].second = j;
					E[idx].first = i;
					E[idx].second = j;
				}
				else {
					E[idx].first = i;
					E[idx].second = j;
				}
				isVisited[idx] = true;
				lastAl = max(lastAl, idx);
			}
		}
		if (lastAl == -1) {
			puts("YES");
			puts("0");
			continue;
		}
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				sim[i][j] = '.';
			}
		}
		for (int i = 0; i <= lastAl; i++) {
			if (!isVisited[i]) continue;
			if (S[i].first == E[i].first) {
				for (int j = S[i].second; j <= E[i].second; j++)
					sim[S[i].first][j] = 'a' + i;
			}
			else if(S[i].second==E[i].second){
				for (int j = S[i].first; j <= E[i].first; j++)
					sim[j][S[i].second] = 'a' + i;
			}
		}
		bool flag = false;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				if (r[i][j] != sim[i][j]) {
					puts("NO");
					flag = true;
					break;
				}
			}
			if (flag) break;
		}
		if (flag) continue;
		puts("YES");
		for (int i = lastAl; i >= 0; i--) {
			if (isVisited[i]) continue;
			S[i].first = S[lastAl].first;
			S[i].second = S[lastAl].second;
			E[i].first = E[lastAl].first;
			E[i].second = E[lastAl].second;
		}
		printf("%d\n", lastAl+1);
		for (int i = 0; i <= lastAl; i++) {
			printf("%d %d %d %d\n", S[i].first, S[i].second, E[i].first, E[i].second);
		}
	}

}