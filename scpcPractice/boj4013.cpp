#include <bits/stdc++.h>
using namespace std;
int N, M, A, B, S, P, val, cnt, sccCnt;
vector<vector<int> > edge, redge;
vector<int> cost, discover, totalCost, sccGroup;
vector<bool> isRest, hasRest;
stack<int> st;
vector<set<int> > newEdge;
vector<int> outDegree;
void flood(int here) {
	sccGroup[here] = sccCnt;
	totalCost[sccCnt] += cost[here];
	if (isRest[here]) hasRest[sccCnt] = true;
	for (int there : edge[here]) {
		if (sccGroup[there]) continue;
		flood(there);
	}
}

void dfs(int here) {
	discover[here] = ++cnt;
	for (int there : redge[here]) {
		if (discover[there]) continue;
		dfs(there);
	}
	st.push(here);
}

void makeGraph() {
	newEdge.resize(sccCnt + 1);
	outDegree.resize(sccCnt + 1);
	for (int i = 1; i <= N; i++) {
		int hereGroup = sccGroup[i];
		for (int there : edge[i]) {
			int thereGroup = sccGroup[there];
			if (hereGroup == thereGroup) continue;
			if (newEdge[hereGroup].find(thereGroup) == newEdge[hereGroup].end()) {
				newEdge[hereGroup].insert(thereGroup);
				outDegree[thereGroup]++;
			}
		}
	}
}

int solution() {
	int ret = 0;
	queue<int> q;
	vector<int> sccCost;
	vector<bool> canGo(sccCnt + 1);
	sccCost.resize(sccCnt + 1);
	int startGroup = sccGroup[S];
	sccCost[startGroup] = totalCost[startGroup];
	canGo[startGroup] = true;
	q.push(startGroup);
	for (int i = 1; i <= sccCnt; i++) {
		if (i == startGroup) continue;
		if (outDegree[i] == 0) {
			q.push(i);
			sccCost[i] = totalCost[i];
		}
	}
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		for (int thereGroup : newEdge[here]) {
			if (canGo[here]) {
				int thereCost = sccCost[here] + totalCost[thereGroup];
				sccCost[thereGroup] = max(sccCost[thereGroup], thereCost);
				canGo[thereGroup] = true;
			}
			if (--outDegree[thereGroup] == 0) {
				q.push(thereGroup);
			}
		}
	}
	for (int i = 1; i <= sccCnt; i++) {
		if (hasRest[i] && canGo[i]) {
			ret = max(ret, sccCost[i]);
		}
	}
	return ret;
}

int main() {
	scanf("%d %d", &N, &M);
	edge.resize(N + 1);
	redge.resize(N + 1);
	isRest.resize(N + 1);
	discover.resize(N + 1);
	cost.resize(N + 1);
	sccGroup.resize(N + 1);
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &A, &B);
		edge[A].push_back(B);
		redge[B].push_back(A);
	}
	for (int i = 1; i <= N; i++) {
		scanf("%d", &cost[i]);
	}
	scanf("%d %d", &S, &P);
	for (int i = 0; i < P; i++) {
		scanf("%d", &val);
		isRest[val] = true;
	}

	for (int i = 1; i <= N; i++) {
		if (discover[i]) continue;
		dfs(i);
	}
	totalCost.push_back(0);
	hasRest.push_back(false);
	while (st.size()) {
		int here = st.top();
		st.pop();
		if (sccGroup[here]) continue;
		totalCost.push_back(0);
		hasRest.push_back(false);
		sccCnt++;
		flood(here);
	}
	makeGraph();
	int ans = solution();
	printf("%d\n", ans);
}