#include <bits/stdc++.h>
using namespace std;
string N, M;
int ans;

void solution(int idx, int midx, int len, int maxx) {
	if (midx == M.size()) {
		ans = max(ans, maxx);
		ans = max(ans, (int)(N.size() - idx));
		return;
	}
	if (idx == N.size()) return;
	if (N[idx] == M[midx]) {
		solution(idx + 1, midx + 1, 0, max(len, maxx));
	}
	solution(idx + 1, midx, len + 1, max(len + 1, maxx));
}
 
int main()
{
	cin >> N >> M;
	solution(0, 0, 0, 0);
	printf("%d\n", ans);
}