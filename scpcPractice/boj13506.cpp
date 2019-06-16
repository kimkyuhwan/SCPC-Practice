#include <bits/stdc++.h>
using namespace std;
char str[1000010];
int N;
vector<int> fail;
void makeFailure(char *str) {
	fail.resize(N);
	for (int i = 1, j = 0; i < N; i++) {
		while (j > 0 && str[i] != str[j]) j = fail[j - 1];
		if (str[i] == str[j]) {
			fail[i] = ++j;
		}
	}
}

int main() {
	scanf("%s", str);
	N = strlen(str);
	makeFailure(str);
	int x = fail[N - 1];
	bool f = false;
	while (x) {
		for (int i = 1; i < N - 1; i++) {
			if (fail[i] == x) {
				for (int j = 0; j < x; j++) {
					printf("%c", str[j]);
				}
				return 0;
			}
		}
		x = fail[x-1];
	}
	if (!f) puts("-1");
	return 0;
}