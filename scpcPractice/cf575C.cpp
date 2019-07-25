#include <bits/stdc++.h>
using namespace std;
const int inf = 1e5;
int q ,n ,x, y, val;
int main()
{
	scanf("%d", &q);
	while (q--) {
		scanf("%d", &n);
		int left = -inf, right = inf, top = inf, bottom = -inf;
		bool flag = true;
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			int state = 0;
			int nl, nr, nt, nb;
			for (int j = 0; j < 4; j++) {
				scanf("%d", &val);
				if (val) state |= (1 << j);
			}
			if ((state & (0x05)) != 0x05) {
				if (state & 1) { nl = -inf, nr = x; }
				else if(state & 4){ nl = x, nr = inf; }
				else { nl = x, nr = x; }
				if (left > nr || nl > right) {
					flag = false;
				}
				else if(nl!=nr){
					left = max(left, nl);
					right = min(right, nr);
				}
				else {
					left = right = nl;
				}
			}
			if ((state & (0x0A)) != 0x0A) {
				if (state & 2) { nb = y, nt = inf; }
				else if (state & 8) { nt = y, nb = -inf; }
				else { nt = nb = y; }
				if (bottom > nt || nb > top) {
					flag = false;
				}
				else if(nb!=nt){
					top = min(top, nt);
					bottom = max(bottom, nb);
				}
				else {
					top = bottom = nt;
				}
			}
		}
		if (!flag) puts("0");
		else {
			printf("1 %d %d\n", left, bottom);
		}
	}
}