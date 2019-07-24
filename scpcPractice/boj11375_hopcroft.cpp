#include <bits/stdc++.h>
using namespace std;
class Hopcroft {
	int N, M;
	vector<int> A, B, level;
	vector<bool> used;
	vector<vector<int> > edges;

public:
	void init(int n, int m) {
		N = n;
		M = m;
		A.assign(N + 1,-1);
		B.assign(M + 1,-1);
		used.assign(N + 1, false);
		level.assign(N + 1, -1);
		edges.assign(N + 1, vector<int>());
	}

	void addEdge(int src, int dst) {
		edges[src].push_back(dst);
	}

	void makeLevelGraph() {
		queue<int> q;
		for (int i = 1; i <= N; i++) {
			if (!used[i]) {
				q.push(i);
				level[i] = 0;
			}
			else {
				level[i] = -1;
			}
		}
		while (!q.empty()) {
			int here = q.front(); q.pop();
			for (int there : edges[here]) {
				int matchedA = B[there];
				if (matchedA != -1 && level[matchedA] == -1) {
					level[matchedA] = level[here] + 1;
					q.push(matchedA);
				}
			}
		}
	}

	bool dfs(int here) {
		for (int there : edges[here]) {
			int matchedA = B[there];
			if (matchedA == -1 || (level[matchedA] == level[here] + 1 && dfs(matchedA))) {
				used[here] = true;
				A[here] = there;
				B[there] = here;
				return true;
			}
		}
		return false;
	}

	int execute() {
		int ret = 0;
		while (1) {
			makeLevelGraph();
			int flow = 0;
			for (int i = 1; i <= N; i++) {
				if (!used[i] && dfs(i)) flow++;
			}
			if (!flow) break;
			ret += flow;
		}
		return ret;
	}
}hf;
int N, M;
int w, work;
void input() {
	scanf("%d %d", &N, &M);
	hf.init(N, M);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &w);
		for (int j = 0; j < w; j++) {
			scanf("%d", &work);
			hf.addEdge(i, work);
		}
	}
}

int main() {
	input();
	int ans = hf.execute();
	printf("%d\n", ans);
	return 0;
}