#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m;

pair<int, pair<int, int> > inp[1010];
vector<int> ans;


int main() {
	scanf("%d %d", &n, &m);
	ans.resize(n, -1);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &inp[i].second.first, &inp[i].second.second);
		inp[i].first = inp[i].second.second - inp[i].second.first;
	}
	for (int i = 0; i < ans.size(); i++) {
		ans[i] = i % 2;
	}
	for (int i : ans) {
		printf("%d", i);
	}
	return 0;
}