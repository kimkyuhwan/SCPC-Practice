#include <bits/stdc++.h>
using namespace std;
string N, M;
vector<int> fail;

void makeFailure() {
	fail.assign(M.size(),0);
	for (int i = 1, j = 0; i < fail.size(); i++) {
		int prev = fail[i - 1];
		while (j > 0 && M[i] != M[j]) j = fail[j - 1];
		if (M[i] == M[j]) fail[i] = ++j;
	}
}

vector<int> executeKMP(string &N, string &M) {
	vector<int> kmpIdx;
	makeFailure();
	for (int i = 0, j=0; i < N.size(); i++) {
		while (j > 0 && N[i] != M[j]) j = fail[j - 1];
		if (N[i] == M[j]) {
			j++;
			if (j == M.size()) {
				kmpIdx.push_back(i-M.size()+2);
				j = fail[j-1];
			}
		}
		else {
			j = fail[j];
		}
	}
	return kmpIdx;
}

int main() {
//	input();
//	vector<int> ans = executeKMP(N, M);
}