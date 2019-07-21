#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, a[110], sum, maxx;
vector<int> ans;
int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		maxx += a[i];
	}
	ans.push_back(1);
	sum += a[0];
	maxx /= 2;
	for (int i = 1; i < n && sum <= maxx; i++) {
		if (a[i]*2 <= a[0]) {
			ans.push_back(i + 1);
			sum += a[i];
		}
	}
	if (sum > maxx) {
		printf("%d\n", ans.size());
		for (int i : ans) {
			printf("%d ", i);
		}
	}
	else {
		puts("0");
	}
	return 0;
}