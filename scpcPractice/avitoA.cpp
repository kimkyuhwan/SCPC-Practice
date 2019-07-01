#include <bits/stdc++.h>
using namespace std;
string str;
int ans;

bool isPalindrome(int l, int r) {
	bool flag = true;
	while (l < r) {
		if (str[l] != str[r]) flag = false;
		l++, r--;
	}
	return flag;
}

int main() {
	cin >> str;
	for (int i = 0; i < str.size(); i++) {
		for (int j = i + 1; j < str.size(); j++) {
			if (!isPalindrome(i, j)) {
				int sum = j - i + 1;
				ans = max(ans, sum);
			}
		}
	}
	cout << ans << endl;
}