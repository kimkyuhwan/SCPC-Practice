#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
int N, M;
int K, S;

vector< vector<int> > sw;
int defaultBright = 0;
int bright = 0;
void turnOnSwitch(int idx) {
	for (int item : sw[idx]) {
		bright ^= (1 << (item - 1));
	}
}


int main() {
	scanf("%d %d", &N, &M);
	sw.resize(N + 1);
	for (int i = 1; i <= M; i++) {
		scanf("%d", &S);
		for (int j = 0; j < S; j++) {
			scanf("%d", &K);
			sw[K].push_back(i);
		}
	}
	int last = (1 << N);
	int sol = 0;
	int allBright = (1 << M)-1;
	for (int i = 0; i < M; i++) {
		scanf("%d", &K);
		if (K == 1) {
			defaultBright += (1 << i);
		}
	}
	for (int state = 0; state < last; state++) {
		bright = 0;
		for (int swItem = 0; swItem < N; swItem++) {
			if (state & (1 << swItem)) {
				turnOnSwitch(swItem + 1);
			}
		}
		if (bright == defaultBright) {
			sol++;
		}
	}
	printf("%d\n", sol);
	return 0;
}