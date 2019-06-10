#include <bits/stdc++.h>
using namespace std;
#define INF 2010
vector<int> ans;
int num[51];
int N;
bool isPrime[INF];
void initPrime() {
	isPrime[2] = true;
	for (int i = 3; i < INF; i += 2) isPrime[i] = true;
	for (int i = 3; i < INF; i += 2) {
		if (!isPrime[i]) continue;
		for (int j = i * 3; j < INF; j += i) {
			isPrime[j] = false;
		}
	}
}class HopCroft {
private:
	int N;
	vector<bool> used;
	vector<bool> fix;
	vector<int> A, B, level;
	vector< vector<int> > edges;
public:
	void init(int N) {
		this->N = N;
		used.assign(N, false);
		A.assign(N, -1);
		B.assign(N, -1);
		level.assign(N, -1);
		fix.assign(N, false);
		fix[0] = true;
		edges.assign(N, vector<int>());
	}

	void clear() {
		used.assign(N, false);
		A.assign(N, -1);
		B.assign(N, -1);
		level.assign(N, -1);
	}

	void addEdge(int src, int dst) {
		edges[src].push_back(dst);
	}

	void makeLevelGraph() {
		queue<int> q;
		for (int i = 0; i < N; i++) {
			if (fix[i]) {
				level[i] = -1;
				continue;
			}
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
				if (fix[there]) continue;
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
			if (fix[there]) continue;
			if (matchedA == -1 || level[matchedA] == level[here] + 1 && dfs(matchedA)) {
				used[here] = true;
				A[here] = there;
				B[there] = here;
				return true;
			}
		}
		return false;
	}

	int execute(int here) {
		int match = 0;

		fix[here] = true;
		while (1) {
			makeLevelGraph();
			int flow = 0;
			for (int i = 0; i < N; i++) {
				if (fix[i]) continue;
				if (!used[i] && dfs(i)) flow++;
			}
			if (flow == 0) break;

			match += flow;
		}
		fix[here] = false;
		clear();
		return match;
	}
};

HopCroft hf;
vector<int> selection;

void input() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &num[i]);
	}
	hf.init(N);
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			int number = num[i] + num[j];
			if (!isPrime[number]) continue;
			if (i == 0) {
				selection.push_back(j);
			}
			hf.addEdge(i, j);
			hf.addEdge(j, i);
		}
	}

}

void solve() {
	for (int i : selection) {
		int flow = hf.execute(i);
		if (flow + 2 == N) {
			ans.push_back(num[i]);
		}
	}
}


int main() {
	initPrime();
	input();
	solve();
	if (ans.empty()) {
		puts("-1");
	}
	else {
		sort(ans.begin(), ans.end());
		for (int here : ans) {
			printf("%d ", here);
		}
	}
}