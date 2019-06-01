#include <cstdio>
#include <vector>
#include <queue>
#include <deque>
using namespace std;
#define LL_MIN -98765432123456789LL
typedef long long ll;
typedef pair<ll, int> pli;
int N, D;
ll dp[200010]; 
ll k[200010];
ll sol = LL_MIN;
int main() {
	scanf("%d %d", &N, &D);
	for (int i = 0; i < N; i++) scanf("%lld", &k[i]);
	priority_queue<pli> pq;
	for (int i = 0; i < N; i++) {
		ll nextDist = k[i];
		while (!pq.empty()) {
			pli here = pq.top(); pq.pop();
			int herePos = here.second;
			ll hereDist = here.first;
			if (herePos < i - D) continue;
			if (hereDist > 0) {
				nextDist += hereDist;
			}
			pq.push({ hereDist,herePos });
			break;
		}
		sol = max(sol, nextDist);
		pq.push({ nextDist, i});
	}


	printf("%lld\n", sol);
	return 0;
}