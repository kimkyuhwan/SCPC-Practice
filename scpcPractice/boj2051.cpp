#include <bits/stdc++.h>
using namespace std;
class HopCroft {
private:
	int N;
	vector<bool> used;
	vector<int> A, B, level;
	vector< vector<int> > edges;
public:
	void init(int N) {
		this->N = N;
		used.assign(N, false);
		A.assign(N, -1);
		B.assign(N, -1);
		level.assign(N, -1);
		edges.assign(N, vector<int>());
	}

	void addEdge(int src, int dst) {
		edges[src].push_back(dst);
	}

	void makeLevelGraph() {
		queue<int> q;
		for (int i = 0; i < N; i++) {
			if (!used[i]) {
				level[i] = 0;
				q.push(i);
			}
			else {
				level[i] = -1;
			}
		}
		while (!q.empty()) {
			int here = q.front();
			q.pop();
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
			if (matchedA == -1 || level[matchedA] == level[here] + 1 && dfs(matchedA)) {
				used[here] = true;
				A[here] = there;
				B[there] = here;
				return true;
			}
		}
		return false;
	}

	int execute() {
		int match = 0;
		while (1) {
			makeLevelGraph();
			int flow = 0;
			for (int i = 0; i < N; i++) {
				if (!used[i] && dfs(i)) flow++;
			}
			if (flow == 0) break;

			match += flow;
		}
		return match;
	}

	void print() {
		vector<int> aa, bb;
		for (int i = 1; i < used.size(); ++i) {
			if (used[i]) {
				if (dfs(i))
					aa.push_back(i);
				else {
					bb.push_back(A[i]);
				}
			}
		}
		printf("%d\n", aa.size());
		for (int i = 0; i < aa.size(); i++) {
			printf("%d ", aa[i]);
			if (i == aa.size() - 1) {
				puts("");
			}
		}
		printf("%d\n", bb.size());
		for (int i = 0; i < bb.size(); i++) {
			printf("%d ", bb[i]);
		}
	}

};

HopCroft hf;
void input() {
	int N, M, K, val;
	scanf("%d %d", &N, &M);
	hf.init(max(N, M)+1);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &K);
		for (int j = 0; j < K; j++) {
			scanf("%d", &val);
			hf.addEdge(i, val);
		}
	}
}


int main() {
	input();
	int ans = hf.execute();
	printf("%d\n", ans);
	hf.print();

	return 0;
}