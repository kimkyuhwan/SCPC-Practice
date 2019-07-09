#include<cstdio>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
int l[4] = { 1,0,-1,0 };
int r[4] = { 0,1,0,-1 };
int visited[1510][1510];
int visited1[1510][1510][4];
const int MAX_V = 2250010;
const int MAX_E = 5000010;
const int MAX = MAX_V * 2;
struct BCCNode {
	bool isArcPoint;
	vector<int> adj;
	BCCNode() :BCCNode(false) {}
	BCCNode(bool flag) :isArcPoint(flag) {}
};
struct BlockCutTree {
	int idx[1510][1510];
	char a[1510][1510];
	int N, M, K, cnt, cnt1;
	int stx, sty, enx, eny;
	int Gn, dcnt;
	int dfsn[MAX_V], ecNum[MAX_V], vcNum[MAX_E];
	stack<pair<int, int>> st;
	unordered_set<int> pi;
	queue<pair<pair<int, int>, int>> qu1;
	unordered_map<int, int> adj[MAX_V];
	BCCNode cn[MAX];
	int depth[MAX];
	void input() {
		Gn = 0; dcnt = 0; cnt = 1, cnt1 = 1;
		scanf("%d %d %d", &N, &M, &K);
		for (int i = 0; i < N; i++) {
			for (int y = 0; y < M; y++) {
				scanf(" %1c", &a[i][y]);
				if (a[i][y] == 'A')stx = i, sty = y;
				if (a[i][y] == 'B')enx = i, eny = y;
			}
		}
		for (int i = 0; i < N; i++) {
			for (int y = 0; y < M; y++) {
				if (a[i][y] == '#')continue;
				idx[i][y] = cnt;
				cnt++;
			}
		}
		for (int i = 0; i < N; i++) {
			for (int y = 0; y < M; y++) {
				if (a[i][y] == '#')continue;
				for (int z = 0; z < 2; z++) {
					int nx = i + l[z];
					int ny = y + r[z];
					if (a[nx][ny] == '#')continue;
					if (nx >= 0 && nx < N&&ny >= 0 && ny < M) {
						adj[idx[i][y]][idx[nx][ny]] = adj[idx[nx][ny]][idx[i][y]] = cnt1;
						cnt1++;
					}
				}
			}
		}
	}
	void construct() {
		memset(dfsn, -1, sizeof(dfsn));
		for (int i = 0; i < cnt; i++) {
			if (dfsn[i] == -1)dfs(i, -1);
			if (adj[i].size() == 1)pi.insert(i);
		}
		for (auto u : pi) {
			cn[Gn] = BCCNode(true);
			for (auto &p : adj[u]) {
				int X = ecNum[p.second];
				cn[Gn].adj.push_back(X);
				cn[X].adj.push_back(Gn);
			}
			vcNum[u] = Gn;
			Gn++;
		}
		queue<pair<int, int>> qu;
		qu.push({ stx,sty });
		visited[stx][sty] = 1;
		while (qu.size()) {
			int cx = qu.front().first; int cy = qu.front().second;
			qu.pop();
			for (int i = 0; i < 4; i++) {
				int nx = cx + l[i]; int ny = cy + r[i];
				if (nx >= 0 && nx < N&&ny >= 0 && ny < M && !visited[nx][ny]) {
					if (a[nx][ny] == '.') {
						visited[nx][ny] = 1;
						qu.push({ nx,ny });
					}
					if (a[nx][ny] == 'B' && !visited1[nx][ny][i]) {
						qu1.push({ { nx,ny },i });
						visited1[nx][ny][i] = 1;
					}
				}
			}
		}
		while (qu1.size()) {
			int cx = qu1.front().first.first; int cy = qu1.front().first.second; int ch = qu1.front().second;
			int ccx = cx + l[ch ^ 2]; int ccy = cy + r[ch ^ 2];
			qu1.pop();
			for (int i = 0; i < 4; i++) {
				int nx = cx + l[i]; int ny = cy + r[i];
				if (nx >= 0 && nx < N&&ny >= 0 && ny < M && !visited1[nx][ny][i] && a[nx][ny] != '#') {
					if (i == ch) {
						visited1[nx][ny][i] = 1;
						qu1.push({ { nx,ny },i });
					}
					else {
						if (vcNum[idx[ccx][ccy]] == vcNum[idx[nx][ny]] && !visited1[cx][cy][i ^ 2]) {
							visited1[cx][cy][i ^ 2] = 1;
							qu1.push({ { cx,cy } ,i ^ 2 });
						}
					}
				}
			}
		}
	}
	void query() {
		for (int i = 0; i < K; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			int update = 0;
			for (int z = 0; z < 4; z++) {
				if (visited1[x][y][z])update |= visited1[x][y][z];
			}
			if (update)puts("YES");
			else puts("NO");
		}
	}
	int dfs(int here, int par) {
		int result = dfsn[here] = dcnt;
		dcnt++;
		for (auto &p : adj[here]) {
			int next = p.first;
			if (next == par)continue;
			if (dfsn[here] > dfsn[next])st.push({ here,next });
			if (dfsn[next] >= 0)result = min(result, dfsn[next]);
			else {
				int tmp = dfs(next, here);
				result = min(result, tmp);
				if (tmp >= dfsn[here]) {
					cn[Gn] = BCCNode();
					while (1) {
						int u = st.top().first; int v = st.top().second;
						st.pop();
						vcNum[u] = Gn; vcNum[v] = Gn;
						if (u == here && v == next)break;
					}
					pi.insert(here);
					Gn++;
				}
			}
		}
		return result;
	}
};
BlockCutTree BCT;
int main()
{
	BCT.input();
	BCT.construct();
	BCT.query();
}