#include <bits/stdc++.h>
using namespace std;

int n, m, a, b;
vector<pair<int, int> > vec, temp;
vector<int> ff;
bool cmp(pair<int, int> a, pair<int, int> b) {
	if (a.first == b.first) {
		return a.second > b.second;
	}
	return a.first < b.first;
}

int main() {
	scanf("%d %d", &n, &m);		
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &a, &b);
		temp.push_back({ a,b });
	}
	sort(temp.begin(), temp.end(), cmp);
	
	vec.push_back(temp[0]);
	for (int i = 1; i < n; i++) {
		if (temp[i - 1].first == temp[i].first) {
			continue;
		}
		vec.push_back(temp[i]);
	}
	puts("");
}