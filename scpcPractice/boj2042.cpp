#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll tree[1000010], val;
ll arr[1000010];
int N, M, K;
int a, b, c;
ll getSum(int i) {
	ll sum = 0;
	while (i > 0) {
		sum += tree[i];
		i -= (i & -i);
	}
	return sum;
}

void update(ll val, int i) {
	while (i <= N) {
		tree[i] += val;
		i += (i & -i);
	}
}

int main() {
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 1; i <= N; i++) {
		scanf("%lld", &arr[i]);
		update(arr[i], i);
	}
	M += K;
	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &a, &b, &c);
		if (a == 1) {
			update(c - arr[b], b);
			arr[b] = c;
		}
		else {
			ll sum = getSum(c) - getSum(b-1);
			printf("%lld\n", sum);
		}
	}
	return 0;
}