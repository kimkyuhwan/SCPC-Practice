#include <bits/stdc++.h>
using namespace std;
int N, a, b;



class Hopcroft {
	vector<int> A, B, level;
	vector<bool> used;
	int N, M;
	vector < vector<pair<int, int> > > edges;

public:
	void init(int n,int m) {
		N = n;
		M = m;
		A.resize(n + 1);
		B.resize(m + 1);
		level.resize(n + 1);
		used.resize(n + 1);
		edges.resize(n + 1);
	}
	
	void clear() {
		fill(A.begin(), A.end(), -1);
		fill(B.begin(), B.end(), -1);
		fill(used.begin(), used.end(), false);
		fill(level.begin(), level.end(), -1);
	}

	void addEdge(int u, int v, int cost) {
		edges[u].push_back({ v,cost });
	}

	void makeLevelGraph(int val) {
		queue<int> q;
		for (int i = 1; i <= N; i++) {
			if (used[i]) {
				level[i] = -1;
			}
			else {
				level[i] = 0;
				q.push(i);
			}
		}
		while (!q.empty()) {
			int here = q.front();
			q.pop();
			for (int i = 0; i < edges[here].size(); i++) {
				int there = edges[here][i].first;
				int thereCost = edges[here][i].second;
				int matched = B[there];
				if (matched != -1 && level[matched] == -1) {
					level[matched] = level[here] + 1;
					q.push(matched);
				}
			}
		}
	}

	bool dfs(int here, int val) {
		for (int i = 0; i < edges[here].size(); i++) {
			int there = edges[here][i].first;
			int thereCost = edges[here][i].second;
			if (thereCost > val) continue;
			int matched = B[there];
			if (matched == -1 || (level[here] + 1 == level[matched] && dfs(matched,val))) {
				used[here] = true;
				A[here] = there;
				B[there] = here;
				return true;
			}
		}
		return false;
	}

	int execute(int val) {
		int match = 0;
		clear();
		while (1) {
			makeLevelGraph(val);
			int flow = 0;
			for (int i = 1; i <= N; i++) {
				if (!used[i] && dfs(i,val)) flow++;
			}
			if (!flow) break;
			match += flow;
		}
		return match;
	}


}hf;




int main()
{
	scanf("%d", &N);
	hf.init(N, 2 * N);
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < 2; j++) {
			scanf("%d %d", &a, &b);
			hf.addEdge(i, a, b);
		}
	}
	int left = 0, right = 1000000;
	while (left < right) {
		int mid = (left + right) >> 1;
		int num = hf.execute(mid);
		if (num != N ) {
			left = mid+1;
		}
		else {
			right = mid;
		}
	}
	printf("%d\n", left);
}