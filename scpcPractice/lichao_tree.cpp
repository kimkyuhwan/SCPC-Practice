#include <bits/stdc++.h>
using namespace std;
#define inf 2e18
typedef long long ll;
typedef pair<ll, ll> Line;

ll f(Line l, ll x, ll time, ll currentCost) {
	return l.first * x + l.second + time *currentCost;
}

struct Node {
	int left, right;
	ll xl, xr;
	Line l;
	 
	Node(int left,int right, ll xl, ll xr, Line l) : left(left), right(right), xl(xl), xr(xr), l(l) {}
};
vector<Node> nodes;

void init(ll xmin, ll xmax) {
	Line l;
	l.first = 0;
	l.second = -inf;
	nodes.emplace_back(-1, -1, xmin, xmax, l);
}

void insert(int n, Line newLine) {
	ll xl = nodes[n].xl;
	ll xr = nodes[n].xr;
	ll xm = (xl + xr) >> 1;

	Line llow = nodes[n].l, lhigh = newLine;
	if (f(llow, xl) > f(lhigh, xl)) swap(llow, lhigh);

	if (f(llow, xr) <= f(lhigh, xr)) {
		nodes[n].l = lhigh;
		return;
	}
	else if (f(llow, xm) < f(lhigh, xm)) {
		nodes[n].l = lhigh;
		if (nodes[n].right == -1) {
			nodes[n].right = nodes.size();
			nodes.push_back({ -1,-1,xm + 1,xr,{0,-inf} });
		}
		insert(nodes[n].right, llow);
	}
	else {
		nodes[n].l = llow;
		if (nodes[n].left == -1) {
			nodes[n].left = nodes.size();
			nodes.push_back({ -1,-1,xl,xm,{ 0,-inf } });
		}
		insert(nodes[n].left, lhigh);
	}
}

ll get(int n, ll xq) {
	if (n == -1) return -inf;
	ll xl = nodes[n].xl, xr = nodes[n].xr;
	ll xm = (xl + xr) >> 1;

	if (xq <= xm) return max(f(nodes[n].l, xq), get(nodes[n].left, xq));
	else return max(f(nodes[n].l, xq), get(nodes[n].right, xq));
}

int main()
{
	init(-2e12, 2e12);

	int Q; scanf("%d", &Q);
	for (int q = 0; q<Q; q++) {
		ll op, a, b, x;
		scanf("%lld", &op);
		if (op == 1) {
			scanf("%lld%lld", &a, &b);
			insert(0, { a,b });
		}
		if (op == 2) {
			scanf("%lld", &x);
			printf("%lld\n", get(0, x));
		}
	}
}