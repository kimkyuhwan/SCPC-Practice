#include <bits/stdc++.h>
using namespace std;
char str[1000010];
vector<int> fail;
void makeFailure(int N) {
	fail.assign(N, 0);
	for (int i = 1, j = 0; i < N; i++) {
		while (j > 0 && str[i] != str[j]) j = fail[j - 1];
		if (str[i] == str[j]) {
			fail[i] = ++j;
		}
	}
}

vector<int> getSelectedNumber(int num) {
	vector<int> ret;
	for (int i = sqrt(num); i >=1 ; i--) {
		if (num%i == 0) {
			ret.push_back(i);
			if (i != sqrt(num)){
				ret.push_back(num/i);
			}
		}
	}
	return ret;
}

bool executeKMP(int src, int dst) {
	makeFailure(dst);
	for (int i = 0, j = 0; i < src; i++) {
		while (j > 0 && str[i] != str[j]) {
			j = fail[j - 1];
			return false;
		}
		if (str[i] == str[j]) {
			j++;
			if (j == dst) {
				j = 0;
			}
		}
		else {
			return false;
		}

	}
	return true;
}

int main() {
	while (scanf(" %s", str) != EOF) {
		if (str[0] == '.' && str[1] == '\0') break;
		int ans = 0;
		int len = strlen(str);
		vector<int> selected = getSelectedNumber(len);
		sort(selected.begin(), selected.end());
		for (int n : selected) {
			if (executeKMP(len, n)) {
				ans = len / n;
				break;
			}
		}
		printf("%d\n", ans);
	}
}