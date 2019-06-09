#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define INF 1e9
int T, n, m, a, b;
vector<vector<int> > edges;
vector<int> matched;
vector<int> ans;
vector<bool> visited;
vector<int> color;
int ccnt[2];
void dfs(int here,int cl) {
	if (color[here] != -1) return;
	color[here] = cl;
	ccnt[cl]++;
	for (int there : edges[here]) {
		if (color[there] == -1)
			dfs(there, (cl + 1) % 2);
	}
}

void print(int here, int cl) {
	if (visited[here]) return;
	visited[here] = true;
	if (color[here] == cl) printf("%d ", here);
	for (int there : edges[here]) {
		if (!visited[there])
			print(there, cl);
	}
}


int main() {
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		scanf("%d %d", &n, &m);
		ccnt[0] = ccnt[1] = 0;
		edges.assign(n + 1, vector<int>());
		visited.assign(n + 1, false);
		matched.assign(n + 1, -1);
		color.assign(n + 1, -1);
		for (int j = 0; j < m; j++) {	
			scanf("%d %d", &a, &b);
			edges[a].push_back(b);
			edges[b].push_back(a);
		}
		vector<pair<int, int> > temp;
		dfs(1,0);
		if (ccnt[0] <= ccnt[1]) {
			printf("%d\n", ccnt[0]);
			print(1, 0);
		}
		else {
			printf("%d\n", ccnt[1]);
			print(1, 1);
		}
		puts("");
		ans.clear();
	}

}

