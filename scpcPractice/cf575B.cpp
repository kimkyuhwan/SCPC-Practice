#include <bits/stdc++.h>
using namespace std;
int val;
int q, arr[200010], N, K, cnt;
int main()
{
	scanf("%d", &q);
	while (q--) {
		scanf("%d %d", &N,&K);
		cnt = 0;
		vector<int> sol;
		bool ans = true;
		for (int i = 0; i < N; i++) {
			scanf("%d", &arr[i]);
			arr[i] %= 2;
			if (arr[i]) {
				if (K == 1) cnt++;
				else {
					sol.push_back(i + 1);
					K--;
				}
			}
		}
		if (K == 1 && cnt % 2 == 1) sol.push_back(N);
		else ans = false;
		if (ans) {
			puts("YES");
			for (int here : sol) { printf("%d ", here); }
			puts("");
		}
		else { puts("NO"); }
	}
	return 0;
}