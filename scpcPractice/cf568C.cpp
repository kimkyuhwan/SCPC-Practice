#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N, M, sum, cnt;
ll arr[200010];
priority_queue<ll> pq, temp;
int main() {
	scanf("%lld %lld", &N, &M);
	for (int i = 0; i < N; i++) {
		scanf("%lld", &arr[i]);
		sum += arr[i];
		while (sum > M) {
			sum -= pq.top();
			temp.push(pq.top());
			pq.pop();
			cnt++;
		}

		printf("%lld ", cnt);
		pq.push(arr[i]);
		temp.push(arr[i]);
		if (temp.top() == arr[i]) {
			temp.pop();
			while (!temp.empty()) {
				sum += temp.top();
				pq.push(temp.top());
				temp.pop();
				cnt--;
			}
		}
	}
	puts("");
}