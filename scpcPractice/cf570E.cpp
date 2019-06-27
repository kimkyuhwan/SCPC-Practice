#include <bits/stdc++.h>
using namespace std;
int ans;
int n, k, cnt, turn;
set<string> st;
string str;
priority_queue<pair<int, string> > q;
int main() {
	cin >> n >> k;
	cin >> str;
	k--;
	q.push({ str.size(), str });
	while (!q.empty() && k>0) {
		string here = q.top().second;
		q.pop();
		int cost = n - here.size() + 1;
		for (int i = 0; i < here.size() && k>0; i++) {
			string there = "";
			for (int j = 0; j < here.size(); j++) {
				if (i == j) continue;
				there += here[j];
			}
			if (st.find(there) == st.end()) {
				st.insert(there);
				q.push({ there.size(),there });
				k--;
				ans += cost;
			}
		}
	}
	if (k > 0) {
		puts("-1");
		return 0;
	}
	printf("%d\n", ans);
}