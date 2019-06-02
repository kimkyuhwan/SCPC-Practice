#include <bits/stdc++.h>
using namespace std;
int N, A, B, C, D;
char S[200010];

bool canGo(int A, int B) {
	for (int i = A+1; i <= B; i++) {
		if (i == B) {
			S[i] = '#';
			return true;
		}
		if (i != N - 1) {
			if (S[i] == '#' && S[i + 1] == '#') return false;
		}
	}
	return false;
}
bool canSwitch() {
	for (int i = B - 1; i <= D-1; i++) {
		if (i < N - 2) {
			if (S[i] == '.' && S[i + 1] == '.' && S[i + 2] == '.') {
				return true;
			}
		}
	}
	return false;
}

int main() {

	scanf("%d %d %d %d %d", &N, &A, &B, &C, &D);
	A--;
	B--;
	C--;
	D--;
	scanf(" %s", S);
	if (C < D) {
		if (canGo(B, D) && canGo(A,C)) puts("Yes");
		else puts("No");
	}
	else if(canSwitch()){
		if (canGo(A, C) && canGo(B, D)) {
			puts("Yes");
		}
		else {
			puts("No");
		}
	}
	else {
		puts("No");
	}
}