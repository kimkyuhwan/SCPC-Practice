#include <bits/stdc++.h>
using namespace std;
string str;
deque<char> temp;
vector<int> fail;

void makeFailure(deque<char> &M) {
	fail.assign(M.size(), 0);
	for (int i = 1, j = 0; i < M.size(); i++) {
		while (j > 0 && M[i] != M[j]) j = fail[j-1];
		if (M[i] == M[j]) fail[i] = ++j;
	}
}
int executeKMP(string &N, deque<char> &M) {
	int ret = 0;
	makeFailure(M);
	for (int i = 0, j = 0; i < N.size(); i++) {
		while (j > 0 && N[i] != M[j]) j = fail[j-1];
		if (N[i] == M[j]) {
			j++;
			if (j == M.size()) {
				ret++;
				j = fail[j - 1];
			}
		}
		else {
			j = fail[j];
		}
	}
	return ret;
}


int main() {
	cin >> str;
	int ans = 0;

	for (int i = 0; i < str.size(); i++) {
		temp.push_back(str[i]);
	}

	for(int i=0;i<str.size();i++){
		executeKMP(str, temp);
		for (int j : fail) {
			ans = max(ans, j);
		}
		temp.pop_front();
	}
	cout << ans << endl;
}