#include <bits/stdc++.h>
using namespace std;
string A, B;
vector<int> fail;

void makeFailure(string &M) {
	fail.assign(M.size(),0);
	for (int i = 1, j = 0; i < M.size(); i++) {
		while (j > 0 && M[i] != M[j]) j = fail[j - 1];
		if (M[i] == M[j]) fail[i] = ++j;
	}
}

int executeKMP(string &N, string &M) {
	int cnt = 0;
	makeFailure(M);
	for (int i = 0, j = 0; i < N.size(); i++) {
		while (j > 0 && N[i] != M[j]) j = fail[j - 1];
		if (N[i] == M[j]) {
			j++;
			if (j == M.size()) {
				cnt++;
				j = fail[j - 1];
			}
		}
		else {
			j = fail[j];
		}
	}
	return cnt;
}

int main() {
	cin >> A;
	A += A;
	A.pop_back();
	cin >> B;
	int ans = executeKMP(A, B);
	cout << ans << endl;
}