#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int N, L, l, d;
vector< pair<int, int> > flow;
ll last;


int main() {
	scanf("%d %d", &N, &L);
	flow.resize(N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &flow[i].first, &flow[i].second);
	}
	for (int i = 0; i < N-1; i++) {
		ll temp = ((L - flow[i].first - flow[i + 1].first)+1)/2;
		if (flow[i].second != flow[i + 1].second) {
			last = max(last, temp);
		}
	}
	printf("%lld", last);
}