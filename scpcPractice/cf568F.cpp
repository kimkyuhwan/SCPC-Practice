#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
int N, M, K, val, state, money;
int people[1 << 10];
int newPeople[1 << 10];
int cnt[1 << 10];
pair<int, int> cost[1 << 10];
pair<int, int> num[1 << 10];
int main(){
	memset(cost, -1, sizeof(cost));
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		scanf("%d", &K);
		state = 0;
		for (int j = 0; j < K; j++) {
			scanf("%d", &val);
			state |= (1 << (val - 1));
		}
		people[state]++;
	}
	for (int i = 0; i < (1 << 10); i++) {
		if (people[i]) {
			for (int j = 0; j < 10; j++) {
				if ((i & j) == i)
				{
					newPeople[j] += people[i];
				}
			}
		}
	}

	for (int i = 0; i < M; i++) {
		scanf(" %d %d",&money, &K);
		state = 0;
		for (int j = 0; j < K; j++) {
			scanf("%d", &val);
			state |= (1 << (val - 1));
		}
		cnt[state]++;
		if (cost[state].first == -1) {
			cost[state].first = money;
			num[state].first = i + 1;
		}
		else if (cost[state].first > money) {
			cost[state].second = cost[state].first;
			num[state].second = num[state].first;
			cost[state].first = money;
			num[state].first = i + 1;
		}
		else if (cost[state].second == -1 || cost[state].second > money) {
			cost[state].second = money;
			num[state].second = i + 1;
		}
	}
	int nPeople = 0;
	int costMax = INF + INF + 10;
	int ans[2];
	for (int i = 0; i < (1 << 10); i++) {
		if (cost[i].first == -1) continue;
		for (int j = 0; j < (1 << 10); j++) {
			if (cost[j].first == -1) continue;
			if (i == j && cnt[i] == 1) continue;
			
			state = i | j;
			int peo = newPeople[state];
			int newCost = cost[i].first + cost[j].first;
			if (i == j) {
				newCost = cost[i].first + cost[i].second;
			}
			if (peo > nPeople) {
				nPeople = peo;
				ans[0] = num[i].first;
				ans[1] = num[j].first;
				if (i == j) {
					ans[1] = num[i].second;
				}
				costMax = newCost;
			}
			else if (peo == nPeople && costMax > newCost) {
				ans[0] = num[i].first;
				ans[1] = num[j].first;
				if (i == j) {
					ans[1] = num[i].second;
				}
				costMax = newCost;
			}
		}
	}
	sort(ans, ans + 2);
	printf("%d %d\n", ans[0], ans[1]);
}