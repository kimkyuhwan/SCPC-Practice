#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define INF 1e9


map<int, int> mmap;

void init() {
	mmap[4] = 0;
	mmap[8] = 1;
	mmap[15] = 2;
	mmap[16] = 3;
	mmap[23] = 4;
	mmap[42] = 5;
}

int arr[500010];
int vec[6];


int main() {
	int n;
	init();
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	int sol = 0;
	for (int i = 0; i < n; i++) {
		if (arr[i] != 4 && arr[i] != 8 && arr[i] != 15 && arr[i] != 16 && arr[i] != 23 && arr[i] != 42) {
			sol++;
		}
		else {
			arr[i] = mmap[arr[i]];
			int here = arr[i];
			vec[here]++;
			int minnn = 1e9;
			for (int j = 0; j <= here; j++) {
				minnn = min(vec[j], minnn);
			}
			sol += vec[here] - minnn;
			vec[here] = minnn;

			if (here == 5) {
				int minn = 1e9;
				for (int j = 0; j <= 5; j++) {
					minn = min(vec[j], minn);
				}
				for (int j = 0; j <= 5; j++) {
					vec[j] -= minn;
				}
			}
		}
	}
	for (int i = 0; i < 6; i++) {
		sol += vec[i];
	}
	printf("%d\n", sol);
	return 0;
}