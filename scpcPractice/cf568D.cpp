#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int N;
int b[200010];
map<int, int> mmap;
bool isPossible(int idx) {
	set<int> a;
	if (idx == 0) {
		for (int i = 2; i < N; i++) a.insert(b[i] - b[i - 1]);
	}
	else if (idx == N - 1) {
		for (int i = 1; i < N-1; i++) a.insert(b[i] - b[i - 1]);
	}
	else {
		for (int i = 1; i < N; i++) {
			if (i == idx) {
				a.insert(b[i + 1] - b[i - 1]);
				i++;
			}
			else a.insert(b[i] - b[i - 1]);
		}
	}
	return a.size() == 1;
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &b[i]);
		mmap[b[i]] = i + 1;
	}
	sort(b, b + N);
	if (N <= 3) {
		puts("1");
		return 0;
	}
	if (isPossible(0)) {
		printf("%d\n", mmap[b[0]]);
		return 0;
	}
	else if (isPossible(1)) {
		printf("%d\n", mmap[b[1]]);
		return 0;
	}
	else if (isPossible(N-1)) {
		printf("%d\n", mmap[b[N-1]]);
		return 0;
	}
	int prev = b[1] - b[0];
	int ccnt = 0;
	for (int i = 2; i < N; i++) {
		if (prev != b[i] - b[i - 1]) {
			if (isPossible(i)) {
				printf("%d\n", mmap[b[i]]);
				return 0;
			}
			else {
				ccnt++;
				if (ccnt == 3) {
					puts("-1");
					return 0;
				}
			}
		}
	}
	puts("-1");
	return 0;
}