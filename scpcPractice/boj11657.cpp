#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
vector<vector<pair<int, int> > > edges;
int N, M;

void input() {
	int a, b, c;
	scanf("%d %d", &N, &M);
	edges.resize(N + 1);
	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &a, &b, &c);
		edges[a].push_back({ b,c });
	}
}



int main() {
	input();
	queue<int> q;
	vector<int> dist(N + 1, INF);
	vector<bool> inQ(N + 1, false);
	inQ[1] = true;
	dist[1] = 0;
	q.push(1);
	int cnt = 0;
	while (!q.empty()) {
		if (cnt >= N) {
			puts("-1");
			return 0;
		}
		int qsz = q.size();
		while (qsz--) {
			int here = q.front(); q.pop();
			inQ[here] = false;
			for (int i = 0; i < edges[here].size(); i++) {
				int there = edges[here][i].first;
				int thereDist = edges[here][i].second;
				if (dist[there] > dist[here] + thereDist) {
					dist[there] = dist[here] + thereDist;
					if (!inQ[there]) {
						q.push(there);
						inQ[there] = true;
					}
				}
			}
		}
		cnt++;
	}
	for (int i = 2; i <= N; i++) {
		if (dist[i] == INF) {
			puts("-1");
		}
		else {
			printf("%d\n", dist[i]);
		}
	}
	return 0;
}