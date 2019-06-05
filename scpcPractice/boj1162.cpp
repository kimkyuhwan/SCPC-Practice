#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <limits.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
vector<vector<pll> > edge;
ll N, M, K, a, b, c;
int main()
{
	scanf("%lld %lld %lld", &N, &M, &K);
	edge = vector < vector<pll> >(N + 1);
	for (int i = 0; i < M; i++)
	{
		scanf("%lld %lld %lld", &a, &b, &c);
		edge[a].push_back({ b, c });
		edge[b].push_back({ a, c });
	}
	priority_queue<pair<pll, ll> > pq;
	vector<vector<ll> > dist(K + 1, vector<ll>(N + 1, -1));
	dist[0][1] = 0;
	pq.push({ { -0, 1 }, 0 });
	while (!pq.empty())
	{
		ll heredist = -pq.top().first.first, here = pq.top().first.second, pozang = pq.top().second;
		pq.pop();
		for (int i = 0; i < edge[here].size(); i++)
		{
			ll there = edge[here][i].first, nextdist = heredist + edge[here][i].second;
			if (pozang < K && (dist[pozang + 1][there] == -1 || dist[pozang + 1][there] > heredist))
			{
				dist[pozang + 1][there] = heredist;
				pq.push({ { -heredist, there }, pozang + 1 });
			}
			if (dist[pozang][there] == -1 || dist[pozang][there] > nextdist)
			{
				dist[pozang][there] = nextdist;
				pq.push({ { -nextdist, there }, pozang });
			}
		}
	}
	ll sol = LLONG_MAX;
	for (int i = 0; i <= K; i++)
		sol = min(sol, dist[i][N]);
	printf("%lld", sol);
}