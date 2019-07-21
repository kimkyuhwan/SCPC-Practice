#include <bits/stdc++.h>
using namespace std;
const int MAX_DEPTH = 18;
const int MAX_ST = 1 << MAX_DEPTH;
const int MAX_ROOT = 10010;
const int MAX_NODE = MAX_ST + MAX_ROOT * MAX_DEPTH;
int T;
int N, M, x, y;
int l, r, b, t;
map<int, vector<int> > input;
vector<int> xVal;
struct Node {
	int val;
	int left, right;
	int nNum;
	int lNum, rNum;
	Node() : Node(-1, -1, -1) {}
	Node(int left, int right, int nNum) : val(0), left(left), right(right), nNum(nNum), lNum(-1), rNum(-1) {}
};

struct PST {
	int Tn;
	int nodeCnt;
	int root[MAX_ROOT];
	Node node[MAX_NODE];

	PST() : Tn(0), nodeCnt(0) {
		fill(root, root + MAX_ROOT, -1);
		root[Tn++] = initialize(0, MAX_ST / 2);
	}

	int initialize(int left, int right) {
		Node &curr = node[nodeCnt] = Node(left, right, nodeCnt);
		nodeCnt++;
		if (left + 1 < right) {
			int mid = (left + right) >> 1;
			curr.lNum = initialize(left, mid);
			curr.rNum = initialize(mid, right);
		}
		return curr.nNum;
	}
	void addNode(int y, int val = 1) {
		root[Tn] = addNode(node[root[Tn - 1]], y, val, 0, MAX_ST / 2);
		Tn++;

	}

	int addNode(Node &shadow, int y, int val, int left, int right) {
		if (right <= y || y < left) return shadow.nNum;
		Node &curr = node[nodeCnt] = Node(left, right, nodeCnt);
		nodeCnt++;
		if (left + 1 == right) 
			curr.val = shadow.val + val;
		else {
			int mid = (left + right) >> 1;
			curr.lNum = addNode(node[shadow.lNum], y, val, left, mid);
			curr.rNum = addNode(node[shadow.rNum], y, val, mid, right);
			curr.val = node[curr.lNum].val + node[curr.rNum].val;
		}
		return curr.nNum;
	}

	int sum(int x, int s, int e) {
		return sum(node[root[x]], s, e);
	}
	int sum(Node &curr, int s, int e) {
		if (e <= curr.left || curr.right <= s) 
			return 0;
		if (s <= curr.left && curr.right <= e) 
			return curr.val;
		return sum(node[curr.lNum], s, e) + sum(node[curr.rNum], s, e);
	}

}*pst;


int main() {
	scanf("%d", &T);
	while (T--) {
		pst = new PST();
		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &x, &y);
			input[x].push_back(y);
		}
		xVal.push_back(-1);
		vector<int> psum;
		psum.push_back(0);
		for (auto it = input.begin(); it != input.end(); it++) {
			int val = psum.back();
			psum.push_back(val);
			int xx = it->first;
			xVal.push_back(xx);
			for (int yy : it->second) {
				pst->addNode(yy);
				psum.back()++;
			}
		}
		
		int ans = 0;
		for (int i = 0; i < M; i++) {
			scanf("%d %d %d %d", &l, &r, &b, &t);
			int rr = upper_bound(xVal.begin(), xVal.end(), r) - xVal.begin();
			int ll = lower_bound(xVal.begin(), xVal.end(), l) - xVal.begin();
			ans += pst->sum(psum[rr-1], b, t+1);
			ans -= pst->sum(psum[ll-1], b, t+1);
		}
		printf("%d\n", ans);
		xVal.clear();
		input.clear();
	}
	return 0;
}