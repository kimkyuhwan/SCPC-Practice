#include <bits/stdc++.h>
using namespace std;
string str;
int A, B;
int main() {
	cin >> str;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == 'o') A++;
		else B++;
	}
	if (A == 0) {
		puts("YES");
		return 0;
	}
	if (B%A == 0) {
		puts("YES");
	}
	else {
		puts("NO");
	}
}