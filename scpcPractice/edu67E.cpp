#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll sum, n;
int u, v;
vector<vector<int> > adj;

ll numberOfNode[200010];
ll sumOfChild[200010];
ll solChild[200010];
ll minChild[200010];
ll getChild(int here=1) {
	ll &ret = numberOfNode[here];
	ret = 1;
	for (int there : adj[here]) {
		if (numberOfNode[there] != 0) continue;
		ret += getChild(there);
	}
	return ret;
}

ll getSum(int here = 1) {
	ll &ret = sumOfChild[here];
	ret = numberOfNode[here];
	bool isLeaf = true;
	for (int there : adj[here]) {
		if (sumOfChild[there] != 0) continue;
		ret += getSum(there);
		minChild[here] = min(minChild[here], numberOfNode[there]);
		isLeaf = false;
	}
	if (isLeaf) minChild[here] = 0;
	return ret;
}

ll maxx = 0;
ll getSolution(int here, ll minus, ll sum, ll cnt, ll nn) {
	ll &ret = solChild[here];
	ret = numberOfNode[here];
	bool isLeaf = true;
	for (int there : adj[here]) {
		ll nextSum = sum;
		if (solChild[there] != 0) continue;
		if (here == 1) nn = numberOfNode[there] + 1;
		else {
			nextSum += numberOfNode[there];
		}
		isLeaf = false;
		ll nextMinus = minus - numberOfNode[there];
		ret = getSolution(there,minus+numberOfNode[there], nextSum,cnt+1,nn);
	}
	if (isLeaf) {
		maxx = max(maxx, n*cnt - sum - minus+(n+1-nn));
	}
	return ret;
}

int main()
{
	freopen("input.txt", "r", stdin);
	scanf("%lld", &n);
	adj.resize(n + 1);
	memset(minChild, 0x3f, sizeof(minChild));
	for (int i = 0; i < n-1; i++) {
		scanf("%d %d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	getChild(); 
	getSum();
	getSolution(1, 0, 0, 0, 0);
	for (int there : adj[1]) {
		sum += sumOfChild[there];
	}

	printf("%lld\n", sum + maxx);
}