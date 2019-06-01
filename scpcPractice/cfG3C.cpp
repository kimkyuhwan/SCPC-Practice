#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N;
ll a[300010];
int pos[300010];
vector<pair<int, int> > ans;
bool isPossibleChange(int src, int dst) {
	return abs(src - dst) >= (N / 2);
}
int getRange(int i) {
	if (1 <= i && i <= N / 2) {
		return 0;
	}
	return 1;
}
void mySwap(const int src,const int dst) {
	ans.push_back({ src,dst });
	ll temp = a[src];
	a[src] = a[dst];
	a[dst] = temp;
	pos[a[src]] = src;
	pos[a[dst]] = dst;

}

int main() {
	scanf("%lld", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%lld", &a[i]);
		pos[a[i]] = i;
	}
	for (int i = 1; i <= N; i++) {
		if (pos[i] == i) continue;
		if (isPossibleChange(i, pos[i])) {
			int tempI = i;
			int tempJ = pos[i];
			if (tempI > tempJ) {
				swap(tempI, tempJ);
			}
			mySwap(tempI, tempJ);
		}
		else {
			int tempI = i;
			int tempJ = pos[i];
			if (tempI > tempJ) {
				swap(tempI, tempJ);
			}
			int ri = getRange(tempI);
			int rj = getRange(tempJ);
			if (ri == 0 && rj == 0) {
				mySwap(tempI, N);
				mySwap(tempJ, N);
				mySwap(tempI, N);
			}
			else if (ri == 0 && rj == 1) {
				mySwap(1, tempJ);
				mySwap(1, N);
				mySwap(tempI, N);
				mySwap(1, N);
				mySwap(1, tempJ);
			}
			else{
				mySwap(1, tempI);
				mySwap(1, tempJ);
				mySwap(1, tempI);
			}
		}
	}
	printf("%d\n", ans.size());
	for (int i = 0; i < ans.size(); i++) {
		printf("%d %d\n", ans[i].first, ans[i].second);
	}

}