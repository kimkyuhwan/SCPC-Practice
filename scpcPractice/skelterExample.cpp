#include <bits/stdc++.h>
using namespace std;
int parseToInt(string A) {
	int ret = 0;
	int N = A.size();
	for (int i = N - 1; i >= 0; i--) {
		ret *= 10;
		ret += A[i] - '0';
	}
	return ret;
}


vector<string> solve(string A) {
	string temp = "";
	vector<string> vec;
	bool isNumber = false;
	bool isWrong = false;
	for (int i = 0; i<A.size(); i++) {
		if (A[i] == '[' || A[i] == ']' || A[i]==' ') continue;
		else if (A[i] == ',') {
			if (!isWrong && isNumber) {
				vec.push_back(temp);
			}
			temp = "";
			isNumber = false;
			isWrong = false;
		}
		else if (A[i] >= '0' && A[i] <= '9') {
			temp += A[i];
			isNumber = true;
		}
		else {
			isWrong = true;
		}
	}
	return vec;
}


string A = "[[13333333333333333333333333333], 24444444444, [[3,4], 5], [[[]]], [[[6]]], 7, 8, []]";

int main() {
	auto ans = solve(A);
	printf("[");
	for (int i = 0; i < ans.size();i++) {
		cout << ans[i];
		if (i != ans.size() - 1) {
			printf(", ");
		}
	}
	puts("]");
}