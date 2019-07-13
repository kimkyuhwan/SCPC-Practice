#include <bits/stdc++.h>
using namespace std;
int num;
char mps;
int cnt[10][3];
int main()
{
	int ans = 2;
	for (int i = 0; i < 3; i++) {
		scanf("%1d%c", &num, &mps);
		if (mps == 'm') {
			int ccnt=++cnt[num][0];
			ans = min(3 - ccnt, ans);
		}
		else if (mps == 'p') {
			int ccnt = ++cnt[num][1];
			ans = min(3 - ccnt, ans);
		}
		else if (mps == 's') {
			int ccnt = ++cnt[num][2];
			ans = min(3 - ccnt, ans);
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j <= 8; j++) {
			if (j <= 7) {
				if (cnt[j][i] != 0 && cnt[j + 1][i] != 0 && cnt[j + 2][i] != 0) {
					ans = 0;
				}
				if (cnt[j][i] != 0 && cnt[j + 2][i] != 0) {
					ans = min(1, ans);
				}
			}
			if (cnt[j][i] != 0 && cnt[j+1][i] != 0) {
				ans = min(1, ans);
			}
		}
	}
	printf("%d\n", ans);
}