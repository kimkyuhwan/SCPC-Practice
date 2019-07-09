#include <bits/stdc++.h>
using namespace std;
#define inf 2e18
typedef long long ll;
typedef pair<ll, ll> Line;

ll f(Line l, ll x) {
	return l.first * x + l.second;
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

int main()
{

}