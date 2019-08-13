#include <bits/stdc++.h>
using namespace std;
int q, n, val;
int cnt[10010];
vector<int> vec;
int main() {
	scanf("%d", &q);
	while (q--) {
		memset(cnt, 0, sizeof(cnt));
		vec.clear();
		scanf("%d", &n);
		n *= 4;
		for (int i = 0; i < n; i++) {
			scanf("%d", &val);
			cnt[val]++;
			if (cnt[val] % 2 == 0) {
				vec.push_back(val);
			}
		}
		bool sol = true;
		if (vec.size() != n / 2) {
			puts("NO");
			continue;
		} 
		sort(vec.begin(), vec.end());
		int maxx = vec.front()*vec.back();
		int sz = vec.size();
		for (int i = 1; i < vec.size() / 2; i++) {
			int w = vec[i] * vec[sz - 1 - i];
			if (maxx != w) {
				sol = false;
				break;
			}
		}
		if (sol) puts("YES");
		else puts("NO");
	}
}