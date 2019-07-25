#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;
map<char, int> al;
int q, N, K, ans;
char str[200010];
int num[200010];
int main() {
	al['R'] = 0, al['G'] = 1, al['B'] = 2;
	scanf("%d", &q);
	while (q--) {
		scanf("%d %d", &N, &K);
		scanf(" %s", str);
		for (int i = 0; i < N; i++) {
			num[i] = al[str[i]];
		}
		ans = N;
		vector<pair<int, int> > vec[3];
		for (int k = 0; k < 3; k++) {
			int start = k;
			int s = 0, e = 0;
			for (int i = 0; i < N; i++) {
				if (start == num[i]) {
					e++;
				}
				else {
					if (s != e) vec[k].push_back({ s,e });
					s = e = i+1;
				}
				start = (start + 1) % 3;
			}
			if (s != e) vec[k].push_back({ s,e });
		}
		for (int k = 0; k < 3; k++) {
			int back=0;
			int totalLength = 0;
			int totalCost = 0;
			queue<int> ll, cc;
			for (int i = 0; i < vec[k].size(); i++) {
				int len = vec[k][i].second - vec[k][i].first;
				totalLength += len;
				ll.push(len);
				if (len >= K) {
					ans = 0;
					break;
				}
				if (i == 0) {
					int kk = max(0, K - len);
					ans = min(ans, kk);
					back = vec[k][i].second;
				}
				else {
					int cost = vec[k][i].first - back;
					totalCost += cost;
					totalLength += cost;
					cc.push(cost);
					back = vec[k][i].second;
					int kk = max(0, K - totalLength);
					ans = min(ans, totalCost + kk);

					while(totalLength >= K) {
						kk = max(0, K - totalLength);
						ans = min(ans, totalCost + kk);
						totalLength-=(ll.front()+cc.front());
						totalCost -= cc.front();
						ll.pop();
						cc.pop();
					}
					kk = max(0, K - totalLength);
					ans = min(ans, totalCost + kk);

				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}