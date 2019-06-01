#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;
typedef long long ll;
map<ll, ll> mmap;
int N, M;
ll A, B, C;
int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		scanf("%lld", &A);
		mmap[-A]++;
	}
	for (int i = 0; i < M; i++) {
		scanf("%lld %lld", &B, &C);
		mmap[-C] += B;
	}
	ll sol = 0;
	ll cnt = N;
	for (auto it = mmap.begin(); it != mmap.end(); it++) {
		ll cost = min(cnt, it->second);
		if (cost == 0) break;


		sol -= it->first*cost;
		cnt -= cost;
	}
	printf("%lld\n", sol);
}