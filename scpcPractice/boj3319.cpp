#include <bits/stdc++.h>
using namespace std;
#define inf 2e18
typedef long long ll;
const int MAXN = 100007;
typedef long long ll;
typedef pair<pair<ll, ll>,int> Line;
int N;
int U, V, D;
ll t, s;
vector<vector<pair<int, ll> > > edges;
vector<pair<ll, ll> > ele;
int root[MAXN];
ll d[MAXN], dtime[MAXN], ans[MAXN];

struct convex {
	int sz;
	int id;
};

int main() {
	scanf("%d", &N);
	edges.resize(N + 1);
	ele.resize(N + 1);
	for (int i = 1; i < N; i++) {
		scanf("%d %d %lld", &U, &V, &D);
		edges[U].push_back({ V,D });
		edges[V].push_back({ U,D });
	}
	for (int i = 2; i <= N; i++) {
		scanf("%lld %lld", &t, &s);
		ele[i] = { t,s };	
	}
	for (int i = 2; i <= N; i++) {
		printf("%lld\n", dtime[i]);
	}
	return 0;
}