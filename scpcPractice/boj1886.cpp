#include <bits/stdc++.h>
using namespace std;

int N, M, DoorCnt;
char mmap[13][13];
int door[13][13];
void input() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf(" %c", &mmap[i][j]);
			if (mmap[i][j] == 'D') {
				door[i][j] = ++DoorCnt;
			}
		}
	}
	
}

void solve() {
	for (int t = 0; t <= 150; t++) {



	}
}

int main() {
	input();
	solve();
}