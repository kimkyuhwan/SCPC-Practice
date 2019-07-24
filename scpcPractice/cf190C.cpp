#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100007;
int n;
int a, b;
vector<vector<int> > edges;
int depth[MAXN], numberOfChild[MAXN], cut[MAXN];
int p[MAXN];
int alpha[MAXN];
int getSize(int here, int parent) {
	numberOfChild[here] = 1;
	for (int there : edges[here]) {
		if (there == parent || cut[there]) continue;
		numberOfChild[here] += getSize(there, here);
	}
	return numberOfChild[here];
}

int findCenter(int here, int parent, int cap) {
	for (int there : edges[here]) {
		if (there == parent || cut[there]) continue;
		if (numberOfChild[there] > cap) return findCenter(there, here, cap);
	}
	return here;
}


void decompose(int here, int cnt) {
	int sz = getSize(here, -1);
	int center = findCenter(here, -1, sz / 2);
	cut[center] = 1;
	alpha[center] = cnt;
	for (int there : edges[center]) {
		if (!cut[there]) decompose(there,cnt+1);
	}
}


int main() {
	scanf("%d", &n);
	edges.resize(n + 1);
	for (int i = 1; i < n; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	decompose(1, 0);
	for (int i = 1; i <= n; i++) {
		printf("%c ", 'A' + alpha[i]);
	}

}