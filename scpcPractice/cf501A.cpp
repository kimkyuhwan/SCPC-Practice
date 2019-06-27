#include <bits/stdc++.h>
using namespace std;
int n, m, l ,r, cnt;
int visited[110];
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &l, &r);
		for (int j = l; j <= r; j++) {
			if (!visited[j]) {
				visited[j] = true;
				cnt++;
			}
		}
	}
	printf("%d\n", m - cnt);
	for (int i = 1; i <= m; i++) {
		if (visited[i]) continue;
		printf("%d ", i);
	}
}