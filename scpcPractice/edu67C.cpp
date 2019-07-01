#include <bits/stdc++.h>
using namespace std;
typedef pair<int, pair<int, int> > p;
int n, m;
vector<p> vec;
vector<int> ans;
vector<int> upDown; // down = 1
int main() {
	scanf("%d %d", &n, &m);
	vec.resize(m);
	ans.resize(n, 1);
	upDown.resize(n);
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &vec[i].first, &vec[i].second.first, &vec[i].second.second);
		if (vec[i].first == 1) {
			for (int j = vec[i].second.first - 1; j < vec[i].second.second-1; j++) {
				upDown[j] = 1;
			}
		}
	}
	bool flag = true;
	for (int i = 0; i < m; i++) {
		if (vec[i].first == 0) {
			
			for (int j = vec[i].second.first-1; j < vec[i].second.second-1; j++) {
				if (upDown[j] != 1) {
					ans[j] = n+2-j;
					break;
				}
				if (j == vec[i].second.second - 2) flag = false;
			}
		}
	}
	if (!flag) {
		puts("NO");
	}
	else {
		puts("YES");
		for (int i : ans) {
			printf("%d ", i);
		}
	}
}