#include <bits/stdc++.h>
using namespace std;
int T, N, M, A, B, W, cnt;
int cost[1010];
int dist[1010];
int indegree[1010];
vector<vector<int> > adj;
int bfs(int dest) {
	queue<int> q;
	for (int i = 1; i <= N; i++) {
		if (indegree[i] == 0) {
			q.push(i);
			dist[i] = cost[i];
		}
	}
	while (!q.empty()) {
		int here = q.front(); q.pop();
		for (int there : adj[here]) {
			indegree[there]--;
			if (indegree[there] == 0) {
				q.push(there);
			}
			dist[there] = max(dist[there], dist[here] + cost[there]);
		}
	}
	
	return dist[dest];
}

int main() {
	scanf("%d", &T);
	for (int i = 1; i <= T; i++) {
		memset(indegree, 0, sizeof(indegree));
		memset(dist, 0, sizeof(dist));
		scanf("%d %d", &N, &M);
		cnt = 0;
		for (int j = 1; j <= N; j++) scanf("%d", &cost[j]);
		adj.assign(N + 1, vector<int>());
		for (int j = 0; j < M; j++) {
			scanf("%d %d", &A, &B);
			adj[A].push_back(B);
			indegree[B]++;
		}
		scanf("%d", &W);
		printf("%d\n", bfs(W));
	}
}