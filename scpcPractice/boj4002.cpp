#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 100007;
ll N, M, ans;
int P;
ll cost[MAXN];
ll lead[MAXN];
ll totalCost[MAXN];
int cntChild[MAXN];
int nodePtr[MAXN];
vector<vector<int> > childs;
vector<priority_queue<ll> > node;
int nodeCnt;

void dfs(int here) {
	ll currentLead = lead[here];
	cntChild[here] = 1;
	int maxxChildNumber = -1;
	totalCost[here] = cost[here];
	for (int child : childs[here]) {
		dfs(child);
		if (maxxChildNumber == -1) maxxChildNumber = child;
		else if (node[nodePtr[maxxChildNumber]].size() < node[nodePtr[child]].size()) maxxChildNumber = child;
		nodePtr[here] = nodePtr[maxxChildNumber];
	}
	if (maxxChildNumber == -1) {
		node.push_back(priority_queue<ll>());
		nodeCnt++;
		node.back().push(cost[here]);
		nodePtr[here] = nodeCnt - 1;
		ans = max(ans, cntChild[here] * currentLead);
		return;
	}
	int hereNode = nodePtr[here];
	node[hereNode].push(cost[here]);
	cntChild[here] += cntChild[maxxChildNumber];
	totalCost[here] += totalCost[maxxChildNumber];
	for (int child : childs[here]) {
		if (maxxChildNumber == child) continue;
		int childPtr = nodePtr[child];
		totalCost[here] += totalCost[child];
		cntChild[here] += cntChild[child];
		while(!node[childPtr].empty()) {
			node[hereNode].push(node[childPtr].top());
			node[childPtr].pop();
		}
	}
	priority_queue<ll> &pq = node[hereNode];
	while(totalCost[here]>M){
		totalCost[here] -= pq.top();
		pq.pop();
		cntChild[here]--;
	}
	ans = max(ans, cntChild[here] *currentLead);
}


int main() {
	scanf("%lld %lld", &N, &M);
	childs.resize(N + 1);
	for (int i = 1; i <= N; i++) {
		scanf("%d %lld %lld", &P, &cost[i], &lead[i]);
		if (P == 0) continue;
		childs[P].push_back(i);
	}
	dfs(1);
	printf("%lld\n", ans);
}