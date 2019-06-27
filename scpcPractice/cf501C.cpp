#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m, ans;
ll sum;

priority_queue<ll> pq;
pair<ll, ll> val[100010];
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%lld %lld", &val[i].first, &val[i].second);
		sum += val[i].first;
		pq.push(val[i].first - val[i].second);
	}
	while (!pq.empty() && m < sum) {
		int here = pq.top();
		pq.pop();
		ans++;
		sum -= here;
	}
	if (m < sum) {
		puts("-1");
		return 0;
	}
	printf("%d\n", ans);
}