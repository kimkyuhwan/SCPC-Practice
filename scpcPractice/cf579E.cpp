#include <bits/stdc++.h>
using namespace std;
int n, val, ans;
map<int, int> mmap;
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &val);
		mmap[val]++;
	}
	for (auto it = mmap.begin(); it != mmap.end(); it++) {
		int cur = it->first;
		if (cur > 150000) break;
		int pre = cur - 1;
		int nxt = cur + 1;
		if (mmap[cur]>0 && pre>=1 && mmap[pre] == 0) {
			mmap[pre]++;
			mmap[cur]--;
		}
		if (mmap[cur] > 1) { 
			mmap[nxt]++;
			mmap[cur]--;
		}
	}
	for (auto it=mmap.begin(); it != mmap.end(); it++) {
		if (it->second > 0) {
			ans++;
		}
	}
	printf("%d\n", ans);
	
}