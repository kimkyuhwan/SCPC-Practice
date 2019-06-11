#include <bits/stdc++.h>
using namespace std;
bool matched[100010][501];
vector<int> fail;
string str, temp;
int len[510];
int dp[100010], n;
int ddp[100010];
void makeFailure(string &M) {
	fail.assign(M.size(), 0);
	for (int i = 1, j = 0; i < M.size(); i++) {
		while (j > 0 && M[i] != M[j]) j = fail[j - 1];
		if (M[i] == M[j]) fail[i] = ++j;
	}
}

void executeKMP(string &N, string &M, int idx) {
	makeFailure(M);
	for (int i = 0, j = 0; i < N.size(); i++) {
		while (j > 0 && N[i] != M[j]) j = fail[j - 1];
		if (N[i] == M[j]) {
			j++;
			if (j == M.size()) {
				int here = i - j + 1;
				matched[here][idx] = true;
				j = fail[j - 1];
			}
		}
		else {
			j = fail[j];
		}
	}
}

int solve(int idx) {
	if (idx == str.size()) return 0;
	int &ret = dp[idx];
	if (ret != -1) return ret;
	ret = solve(idx + 1);
	for (int here = 0; here < n; here++) {
		if (matched[idx][here]) {
			ret = max(ret, len[here] + solve(idx + len[here]));
		}
	}
	return ret;
}
int main() {
	memset(dp, -1, sizeof(dp));
	cin >> str;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> temp;
		len[i] = temp.size();
		executeKMP(str, temp, i);
	}
	int sol = solve(0);
	cout << sol << endl;
}