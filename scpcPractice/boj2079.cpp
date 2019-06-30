#include <bits/stdc++.h>
using namespace std;
char str[4010];
int p[4010];
int N;

void initPalindrome() {
	int r=-1, c=-1, k;
	for (int i = 0; i < N; i++) {
		if (c == -1) k = 0;
		else k = p[2 * c - i] <= c + p[c] - i ? p[2 * c - i] : c + p[c] - i;
		while (i - k - 1 >= 0 && i + k + 1 < N && str[i - k - 1] == str[i + k + 1]) k++;
		if (i + k > c + p[c]) c = i;
		p[i] = k;
	}
}


int main() {
	scanf(" %s", str);
	N = strlen(str);
	for (int i = N - 1; i >= 0; i--) {
		str[(i << 1) + 1] = str[i];
		str[(i << 1)] = '#';
	}
	N <<= 1;
	str[N++] = '#';
	initPalindrome();


}