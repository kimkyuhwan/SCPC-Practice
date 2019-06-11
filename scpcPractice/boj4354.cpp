#include <bits/stdc++.h>
using namespace std;
string str;
vector<int> fail;

void makeFailure(string &M) {
	fail.assign(M.size(), 0);
	for (int i = 1, j = 0; i < M.size(); i++) {
		while (j > 0 && M[i] != M[j]) j = fail[j - 1];
		if (M[i] == M[j]) fail[i] = ++j;
	}
}

bool executeKMP(string &N, string &M) {
	makeFailure(M);
	for (int i = 0, j=0; i < N.size(); i++) {
		while (j > 0 && N[i] != M[j]) {
			j = fail[j - 1];
			return false;
		}
		if (N[i] == M[j]) {
			j++;
			if (j == M.size()) {
				j = 0;
			}
		}
		else {
			return false;
		}
	}
	return true;
}

int solve() {
	int n = str.size();
	string temp;
	vector<int> selected;
	for (int i = 1; i <= sqrt(n); i++) {
		
		if (n%i == 0) {
			if (i == sqrt(n)) {
				selected.push_back(i);
			}
			else {
				selected.push_back(i);
				selected.push_back(n / i);
			}
		}
	}
	sort(selected.begin(), selected.end());
	int pos = 0;
	for (int i = 0; i < n; i++) {
		int here = selected[pos];
		temp.push_back(str[i]);
		if (here - 1 == i) {
			pos++;
			if (executeKMP(str, temp)) {
				return n / here;
			}
		}
	}
	return 1;
}


int main() {
	while (cin >> str) {
		if (str == ".") break;
		int ans = solve();
		cout << ans << endl;
	}
}