#include <bits/stdc++.h>
using namespace std;
int T, N, M;
int u, v, cnt, sccCnt;
vector<vector<int> > edge, redge;
vector<int> discover, scc, indegree;
stack<int> st;
vector<set<int> > newEdge;
void dfs(int here) {
	discover[here] = ++cnt;
	int ret = discover[here];
	for (int there : redge[here]) {
		if (discover[there]) continue;
		dfs(there);
	}
	st.push(here);
}

void flood(int here) {
	scc[here] = sccCnt;
	for (int there : edge[here]) {
		if (scc[there]) continue;
		flood(there);
	}
}

int makeGraph() {
	newEdge.assign(sccCnt + 1,set<int>());
	indegree.assign(sccCnt + 1, 0);
	for (int i = 1; i <= N; i++) {
		int group = scc[i];
		for (int there : edge[i]) {
			int thereGroup = scc[there];
			if (group == thereGroup) continue;
			newEdge[group].insert(thereGroup);
			indegree[thereGroup]++;
		}
	}
	int ans = 0;
	for (int i = 1; i <= sccCnt; i++) {
		if (indegree[i] == 0) {
			ans++;
		}
	}
	return ans;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &N, &M);
		edge.assign(N + 1,vector<int>());
		redge.assign(N + 1, vector<int>());
		discover.assign(N + 1, 0);
		scc.assign(N + 1, 0);
		cnt = 0;
		sccCnt = 0;
		for (int i = 0; i < M; i++) {
			scanf("%d %d", &u, &v);
			edge[u].push_back(v);
			redge[v].push_back(u);
		}
		for (int i = 1; i <= N; i++) {
			if (discover[i]) continue;
			dfs(i);
		}
		while (st.size()) {
			int here = st.top();
			st.pop();
			if (scc[here]) continue;
			sccCnt++;
			flood(here);
		}
		int ans = makeGraph();
		printf("%d\n", ans);
	}

}