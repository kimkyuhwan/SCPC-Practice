#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int sum[1010][5];
int score[1010];
int n, m;
char val;
ll ans;
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf(" %c", &val);
			sum[j][val - 'A']++;
		}
	}
	for (int i = 0; i < m; i++) {
		scanf("%d", &score[i]);
	}
	for (int i = 0; i < m; i++) {
		sort(sum[i], sum[i] + 5);
		ans += 1LL * score[i] * sum[i][4];
	}
	printf("%lld\n", ans);
}