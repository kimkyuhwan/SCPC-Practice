#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define INF 1e9
bool isNotPossbile = false;
int dfs(ll here) {
	if (here == 1) return 0;
	int ret = INF;
	bool flag = false;
	if (here % 2 == 0) {
		flag = true;
		ret = dfs(here / 2);
	}
	else if (here % 3 == 0) {
		flag = true;
		ret =dfs(2 * here / 3);
	}
	else if (here % 5 == 0) {
		flag = true;
		ret = dfs(4 * here / 5);
	}
	if (ret==INF || ret==-1) {
		return -1;
	}
	return ret+1;
}


int q;
ll val;
int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &q);
	for (int i = 0; i < q; i++) {
		scanf("%lld", &val);
		printf("%d\n", dfs(val));
	}
	return 0;
}