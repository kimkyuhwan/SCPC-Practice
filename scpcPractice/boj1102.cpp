#include <bits/stdc++.h>
using namespace std;
#define INF (1<<30)
int dp[16][1 << 16], N, P, start;
char onoff[20];
int w[16][16], sol;
int solution(int num, int state)
{
	if (num >= P) return 0;
	int &ret = dp[num][state];
	if (ret != -1) return ret;
	ret = INF;
	for (int i = 0; i < N; i++)
	{
		if ((state & (1 << i)) == 0) continue;
		for (int j = 0; j < N; j++)
		{
			if (state & (1 << j)) continue;
			ret = min(ret, solution(num+1, (state | (1 << j))) + w[i][j]);
		}
	}
	return ret;
}
int main()
{
	memset(dp, -1, sizeof(dp));
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &w[i][j]);
	scanf(" %s %d", onoff, &P);
	int cnt = 0;
	for (int i = 0; i < N; i++)
	{
		if (onoff[i] == 'Y')
		{
			start = (start | (1 << i));
			cnt++;
		}
	}
	sol = INF;
	if (cnt!=0) {
		sol = solution(cnt, start);
	}
	else if (P == 0) {
		sol = 0;
	}
	if (sol >= INF) sol = -1;
	printf("%d", sol);
}