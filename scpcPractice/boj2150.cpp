#include <bits/stdc++.h>
using namespace std;
int number, sccNumber;
vector<int> pre, post, visitScc;
vector<bool> visit;
vector<vector<int> > edge, redge, scc;
int V, E, A, B;
stack<int> st;
void flood(int here) {
	visitScc[here] = ++sccNumber;
	scc.back().push_back(here);
	for (int there : edge[here]) {
		if (visitScc[there]) continue;
		flood(there);
	}
}


void dfs(int here) {
	pre[here] = ++number;
	visit[here] = true;
	for (int there : redge[here]) {
		if (visit[there]) continue;
		dfs(there);
	}
	post[here] = ++number;
	st.push(here);
}


void numbering() {
	for (int i = 1; i <= V; i++) {
		if (visit[i]) continue;
		dfs(i);
	}
}


int main()
{
	scanf("%d %d", &V, &E);
	edge.resize(V + 1);
	redge.resize(V + 1);
	visit.resize(V + 1);
	visitScc.resize(V + 1);
	pre.resize(V + 1);
	post.resize(V + 1);
	for (int i = 0; i < E; i++) {
		scanf("%d %d", &A, &B);
		edge[A].push_back(B);
		redge[B].push_back(A);
	} 
	numbering();

	while (st.size()) {
		int here = st.top();
		st.pop();
		if (visitScc[here]) continue;
		scc.push_back(vector<int>());
		flood(here);
	}
	for (int i = 0; i < scc.size(); i++) {
		sort(scc[i].begin(), scc[i].end());
	}
	sort(scc.begin(), scc.end());
	printf("%d\n", scc.size());
	for (int i = 0; i < scc.size(); i++) {
		for (int j = 0; j < scc[i].size(); j++) {
			printf("%d ", scc[i][j]);
		}
		puts("-1");
	}
}