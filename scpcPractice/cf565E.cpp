#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define INF 1e9
int T, n, m, a, b;
vector<vector<int> > edges;
vector<int> matched;
vector<int> ans[2];
vector<int> color;
void dfs(int here,int cl) {
	if (color[here] != -1) return;
	color[here] = cl;
	ans[cl].push_back(here);
	for (int there : edges[here]) {
		if (color[there] == -1)
			dfs(there, (cl + 1) % 2);
	}
}


int main() {
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		scanf("%d %d", &n, &m);
		edges.assign(n + 1, vector<int>());
		color.assign(n + 1, -1);
		ans[0].clear();
		ans[1].clear();
		for (int j = 0; j < m; j++) {	
			scanf("%d %d", &a, &b);
			edges[a].push_back(b);
			edges[b].push_back(a);
		}
		vector<pair<int, int> > temp;
		dfs(1,0);
		if (ans[0].size() <= ans[1].size()) {
			printf("%d\n", ans[0].size());
			for (int i = 0; i < ans[0].size(); i++) {
				printf("%d ", ans[0][i]);
			}
		}
		else {
			printf("%d\n", ans[1].size());
			for (int i = 0; i < ans[1].size(); i++) {
				printf("%d ", ans[1][i]);
			}
		}
		puts("");
	}

}

