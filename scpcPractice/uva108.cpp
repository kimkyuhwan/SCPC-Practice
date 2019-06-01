#include <cstdio>
#include <algorithm>
using namespace std;
int N;
int arr[110][110];
int psum[110][110];

int getRect(int y1, int x1, int y2, int x2) {
	int ret = psum[y2][x2];
	if (x1) ret -= psum[y2][x1 - 1];
	if (y1) ret -= psum[y1 - 1][x2];
	if (x1 && y1) ret += psum[y1 - 1][x1 - 1];
	return ret;
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &arr[i][j]);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			psum[i][j] = arr[i][j];
			if (i) psum[i][j] += psum[i - 1][j];
			if (j) psum[i][j] += psum[i][j - 1];
			if (i && j) psum[i][j] -= psum[i - 1][j - 1];
		}
	}
	int sol = -1987654321;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = i; k < N; k++) {
				for (int m = j; m < N; m++) {
					sol = max(sol, getRect(i, j, k, m));
				}
			}
		}
	}
	printf("%d\n", sol);
	return 0;
}