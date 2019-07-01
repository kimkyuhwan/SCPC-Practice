#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
map<int, int> mmap;
int N, M, idx, val;
ll ans;
int main() {
	scanf("%d",&N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &idx, &val);
		mmap[idx] = max(mmap[idx], val);
	}
	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &idx, &val);
		mmap[idx] = max(mmap[idx], val);
	}
	for (map<int, int>::iterator it = mmap.begin(); it != mmap.end(); it++) {
		ans += it->second;
	}
	printf("%lld\n", ans);

}