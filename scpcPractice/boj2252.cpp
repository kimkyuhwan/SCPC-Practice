#include <bits/stdc++.h>
using namespace std;
int N, M, A, B;
vector<vector<int> > adj;
vector<int> preVisit, postVisit, ans;
vector<bool> visited;
int cnt;

bool cmp(int i, int j) {
	return postVisit[i] > postVisit[j];
}

void dfs(int here) {
	if (preVisit[here] != 0) return;
	preVisit[here] = ++cnt;
	for (int there : adj[here]) { dfs(there); }
	postVisit[here] = ++cnt;
}

int main()
{
	scanf("%d %d", &N,&M);
	adj.resize(N + 1);
	visited.resize(N + 1);
	preVisit.resize(N + 1);
	postVisit.resize(N + 1);
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &A, &B);
		adj[A].push_back(B);
	}
	ans.resize(N);
	for (int i = 1; i <= N; i++) {
		ans[i - 1] = i;
		dfs(i);	
	}
	sort(ans.begin(), ans.end(), cmp);
	for (int i : ans) {
		printf("%d ", i);
	}
	return 0;
}