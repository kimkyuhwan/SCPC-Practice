#include <bits/stdc++.h>
using namespace std;
char s[1000010];
int psum[1000010][3];
string ans;
vector<int> p[3];
pair<int, int> fb[3];
int main() {
	scanf("%s", s);
	int len = strlen(s);
	for (int i = 0; i < 3; i++) fb[i].first = -1;
	for (int i = 0; i < len; i++) {
		int a = s[i] - 'a';
		for (int j = 0; j < 3; j++) psum[i + 1][j] = psum[i][j];
		psum[i + 1][a]++;
		p[a].push_back(i);
		if (fb[a].first == -1) {
			fb[a].first = i;
		}
		fb[a].second = i;
	}
	int mid = len / 2;
	int pos = mid;
	if (len % 2 == 1) mid++;
	int cnt = 0;
	int ff = 0, bb = len;
	while (cnt < pos) {
		int selectedAlphaBet = -1;
		int selectedSize = 0;
		int selectF, selectB;
		for (int i = 0; i < 3; i++) {
			int nextFidx = lower_bound(p[i].begin(),p[i].end(),ff)-p[i].begin();
			if (nextFidx >= p[i].size()) continue;
			int nextF = p[i][nextFidx];
			int nextBidx = upper_bound(p[i].begin(), p[i].end(), bb) - p[i].begin();
			if (nextBidx < 0) continue;
			int nextB = p[i][nextBidx-1];
			int nextSz = nextB-nextF+1;
			if (selectedSize > nextSz) continue;
			selectedSize = nextSz;
			selectedAlphaBet = i;
			selectF = nextF;
			selectB = nextB;
		}
		if (selectedAlphaBet == -1) {
			break;
		}
		ans.push_back(selectedAlphaBet + 'a');
		ff = selectF+1;
		bb = selectB-1;
		if (selectF != selectB) {
			cnt += 2;
		}
		else {
			cnt++;
			break;
		}
	}
	if (cnt < pos) {
		puts("IMPOSSIBLE");
	}
	else {
		string bak = ans;
		if (cnt % 2 == 1) bak.pop_back();
		reverse(bak.begin(), bak.end());
		cout << ans + bak << endl;
	}
}