#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int N;
typedef pair<pair<int, int>, int> ppi;
vector<ppi> p;
vector<ppi> n;
int x, y;
int main() {

	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d %d", &x, &y);
		if (x < y) {
			p.push_back({ {y,x}, i});
		}
		else if (x > y) {
			n.push_back({ { y,x },i });
		}
	}
	sort(p.rbegin(), p.rend());
	sort(n.begin(), n.end());
	vector<int> sol;
	vector<int> tempP,tempN;
	for (int i = 0; i < p.size(); i++) {
		if (i==0) {
			tempP.push_back(i);
		}
		else{
			int last = p[tempP.back()].first.first;
			if (last <p[i].first.second) {
				break;
			}
			tempP.push_back(i);
		}
	}
	for (int i = 0; i < n.size(); i++) {
		if (i == 0) {
			tempN.push_back(i);
		}
		else {
			int last = n[tempN.back()].first.first;
			if (last > n[i].first.second) {
				break;
			}
			tempN.push_back(i);
		}
	}
	if (tempP.size() < tempN.size()) {
		sol = tempN;
		printf("%d\n", sol.size());
		for (int i = 0; i < sol.size(); i++) {
			printf("%d ", n[sol[i]].second);
		}
	}
	else {
		sol = tempP;
		printf("%d\n", sol.size());
		for (int i = 0; i < sol.size(); i++) {
			printf("%d ", p[sol[i]].second);
		}
	}
	


}