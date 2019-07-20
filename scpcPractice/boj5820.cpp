#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200010;
int sz[MAXN], cut[MAXN], ans;
map<int, int> mp;
int N, K;
int a, b, w;
vector< vector<pair<int, int> > > edges;

int getSize(int here, int parent) {
	sz[here] = 1;
	for (int i = 0; i < edges[here].size(); i++) {
		int there = edges[here][i].first;
		if (parent == there || cut[there]) continue;
		sz[here] += getSize(there, here);
	}
	return sz[here];
}

int findCenter(int here, int parent, int cap) {
	for (int i = 0; i < edges[here].size(); i++) {
		int there = edges[here][i].first;
		if (cut[there] || there == parent) continue;
		if (sz[there] > cap) return findCenter(there, here, cap);
	}
	return here;
}

void compute(int here, int parent, int dist, int depth) {
	if (dist > K) return;
	auto it = mp.find(K - dist);
	if (it != mp.end()) {
		ans = min(ans, it->second + depth);
	}
	for (int i = 0; i < edges[here].size(); i++) {
		int there = edges[here][i].first;
		int weight = edges[here][i].second;
		if (!cut[there] && there != parent) compute(there, here, dist + weight, depth + 1);
	}
}

void add(int here, int parent, int dist, int depth) {
	if (dist > K) return;
	auto it = mp.find(dist);
	if (it != mp.end()) {
		it->second = min(it->second, depth);
	}
	else {
		mp[dist] = depth;
	}
	for (int i = 0; i < edges[here].size(); i++) {
		int there = edges[here][i].first;
		int weight = edges[here][i].second;
		if (cut[there] || there == parent) continue;
		add(there, here, dist + weight, depth + 1);
	}
}

void solution(int here) {
	int sz = getSize(here, -1)/2;
	int center = findCenter(here, -1, sz);
	cut[center] = 1;
	mp.clear(); mp[0] = 0;
	for (int i = 0; i < edges[center].size(); i++) {
		int there = edges[center][i].first;
		int weight = edges[center][i].second;
		if (!cut[there]) {
			compute(there, center, weight, 1);
			add(there, center, weight, 1);
		}
	}
	for (int i = 0; i < edges[center].size(); i++) {
		int there = edges[center][i].first;
		if (!cut[there]) solution(there);
	}
}
int main()
{
	scanf("%d %d", &N, &K);
	edges.resize(N + 1);
	for (int i = 1; i < N; i++) {
		scanf("%d %d %d", &a, &b, &w);
		edges[a].push_back({ b,w });
		edges[b].push_back({ a,w });
	}
	ans = 1e9;
	solution(1);
	if (ans == 1e9) {
		ans = -1;
	}
	printf("%d\n", ans);
	return 0;
}