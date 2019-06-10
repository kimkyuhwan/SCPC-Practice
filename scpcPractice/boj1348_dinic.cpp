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
};

int R, C;
int startVertex, endVertex, numberOfVertex;
char mmap[51][51];
int park[51][51];
int car[51][51];
int dist[51][51];
int parkCnt, carCnt;
int dy[4] = { 0,0,-1,1 };
int dx[4] = { -1,1,0,0 };
int cpDist[110][110];
bool isPossiblePosition(int y, int x) {
	return y >= 0 && y < R && x >= 0 && x < C;
}

void bfs(int y, int x) {
	int carIdx = car[y][x];
	queue<pair<int, int> > q;
	q.push({ y,x });
	memset(dist, -1, sizeof(dist));
	dist[y][x] = 0;
	int cnt = 0;
	while (!q.empty()) {
		int sz = q.size();
		cnt++;
		for (int i = 0; i < sz; i++) {
			int hereY = q.front().first;
			int hereX = q.front().second;
			q.pop();
			for (int k = 0; k<4; k++) {
				int ny = hereY + dy[k];
				int nx = hereX + dx[k];
				if (isPossiblePosition(ny, nx) && mmap[ny][nx] != 'X' && dist[ny][nx]==-1) {
					dist[ny][nx] = cnt;
					if (mmap[ny][nx] == 'P') {
						int parkIdx = park[ny][nx];
						cpDist[carIdx][parkIdx] = dist[ny][nx];
					}
					q.push({ ny,nx });
				}
			}
		}
	}
}


void input() {
	memset(cpDist, 0x3f, sizeof(cpDist));
	scanf("%d %d", &R, &C);
	startVertex = R*C;
	endVertex = startVertex + 1;
	numberOfVertex = endVertex + 1;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			scanf(" %c", &mmap[i][j]);
			if (mmap[i][j] == 'C') {
				car[i][j] = ++carCnt;
			}
			else if (mmap[i][j] == 'P') {
				park[i][j] = ++parkCnt;
			}
		}
	}
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (mmap[i][j] == 'C') {
				bfs(i, j);
			}	
		}
	}
}

bool execute(int val) {
	HopCroft hf;
	hf.init(max(carCnt, parkCnt) + 1);
	for (int i = 1; i <= carCnt; i++) {
		for (int j = 1; j <= parkCnt; j++) {
			if (cpDist[i][j] <= val) {
				hf.addEdge(i, j);
			}
		}
	}
	int cnt = hf.execute();
	return cnt == carCnt;
}

int solve() {
	int L = 0, R = 10000;
	while (L < R) {
		int mid = (L + R) >> 1;
		if (execute(mid)) {
			R = mid;
		}
		else {
			L = mid + 1;
		}
	}
	return L;
}

int main() {
	input();
	int ans = solve();
	if (carCnt == 0) {
		puts("0");
		return 0;
	}
	else if (ans == 0 || ans==10000) {
		puts("-1");
		return 0;
	}
	printf("%d\n", ans);
	return 0;
}