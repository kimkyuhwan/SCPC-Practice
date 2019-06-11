#include <bits/stdc++.h>
using namespace std;
int w, h, sum;
char ch;
vector<vector<int> > aa;
int main() {
	scanf("%d %d", &h, &w);
	aa.resize(h);
	vector<int> selected;
	for (int i = 0; i < h; i++) {
		int cnt = 0;
		for (int j = 0; j < w; j++) {
			scanf(" %c", &ch);
			if (ch == '*') {
				cnt++;
			}
		}
		if (cnt >= 3) {
			selected.push_back(i);
		}
		sum += cnt;
	}

}