#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf = 1e9;
const int MAXN = 100007;
const int MAX_DEPTH = 18;
const int MAX_ST = (1 << MAX_DEPTH);
const int MAX_NODE = MAX_ST + MAXN*MAX_DEPTH;
int n, m, val;
int a, b, c;
int Xn;
map<int, int> dx;
int w[MAXN], x[MAXN];
struct Node {
	int val;
	int left, right;
	int nNum, lNum, rNum;
	Node() : Node(-1, -1, -1) {}
	Node(int left, int right, int nNum) : val(0), left(left), right(right), nNum(nNum), lNum(-1), rNum(-1) {}
};

struct PST {
	int Tn;
	int nodeCnt;
	int root[MAXN];
	Node node[MAX_NODE];

	PST() : Tn(0), nodeCnt(0) {}

	void init() {
		fill(root, root + MAXN, -1);
		root[Tn++] = initialize(1, Xn);
	}

	int initialize(int left, int right) {
		Node &curr = node[nodeCnt] = Node(left, right, nodeCnt);
		nodeCnt++;
		if (left < right) {
			int mid = (left + right) >> 1;
			curr.lNum = initialize(left, mid);
			curr.rNum = initialize(mid + 1, right);
		}
		return curr.nNum;
	}

	void insert(int x, int left, int right) {
		root[Tn] = update(node[root[Tn - 1]], x, 1, left, right);
		Tn++;
	}

	int update(Node &shadow, int x, int val, int left, int right) {
		if (left > x || x > right) return shadow.nNum;

		Node &curr = node[nodeCnt] = Node(left, right, nodeCnt);
		nodeCnt++;

		if (left == right) {
			curr.val = shadow.val + val;
		}
		else {
			int mid = (left + right) >> 1;
			curr.lNum = update(node[shadow.lNum], x, val, left, mid);
			curr.rNum = update(node[shadow.rNum], x, val, mid+1, right);
			curr.val = node[curr.lNum].val + node[curr.rNum].val;
		}
		return curr.nNum;
	}


	int query(Node &lNode, Node &rNode, int k) {
		if (rNode.left == rNode.right) return rNode.left;

		int pivot = node[rNode.lNum].val - node[lNode.lNum].val;
		if (k < pivot) return query(node[lNode.lNum], node[rNode.lNum], k);
		else return query(node[lNode.rNum], node[rNode.rNum], k - pivot);
	}

	int query(int left, int right, int k) {
		return query(node[root[left - 1]], node[root[right]], k);
	}
}pst;


int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &w[i]);
		x[i] = w[i];
	}
	sort(x + 1, x + n + 1);
	Xn = unique(x + 1, x + n + 1) - (x + 1);
	for (int i = 1; i <= Xn; i++) {
		dx[x[i]] = i;
	}
	for (int i = 1; i <= n; i++) {
		w[i] = dx[w[i]];
	}
	pst.init();
	for (int i = 1; i <= n; i++) {
		pst.insert(w[i], 1, Xn);
	}
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &c);
		int ans = pst.query(a, b, c-1);
		printf("%d\n", x[ans]);
	}
	return 0;
}