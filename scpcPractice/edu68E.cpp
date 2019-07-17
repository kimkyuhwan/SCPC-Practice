#include <bits/stdc++.h>
using namespace std;
int n;
int xa, ya, xb, yb;
struct Line {
	int s, e, a;
	vector<int> ins;
	Line(int s, int e, int a) : s(s), e(e), a(a) {}
};
vector<Line> horizon, vertical;

bool cmp(Line a, Line b) {
	return a.a < b.a;
}
int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d %d %d", &xa, &ya, &xb, &yb);
		if (xa == xb) {
			vertical.emplace_back(ya, yb, xa);
		}
		else {
			horizon.emplace_back(xa, xb, ya);
		}
	}
	sort(vertical.begin(), vertical.end(), cmp);
	sort(horizon.begin(), horizon.end(), cmp);
	for (int i = 0; i < vertical.size(); i++) {
		for (int j = 0; j < horizon.size(); j++) {
			if (vertical[i].a >= horizon[j].s && vertical[i].a <= horizon[j].e) {
				vertical[i].ins.push_back(j);
			}
		}
	}
	vector<int> visited(horizon.size());
	vector<bool> updated(horizon.size());

	vector<int> prevVec;
	if (vertical.size() >= 1) {
		for (int i : vertical[0].ins) {
			visited[i] = 1;
			prevVec.push_back(i);
		}
	}
	for (int i = 1; i < vertical.size(); i++) {
		vector<int> curVec;
		fill(updated.begin(), updated.end(), false);
		
		for (int here : vertical[i].ins) {
			if (visited[here] != 0) {
				visited[here]++;
				updated[here] = true;
				curVec.push_back(here);
			}
		}
		for (int here : prevVec) {
			if (!updated[here]) visited[here] = 0;
		}
		prevVec = curVec;
	}
}