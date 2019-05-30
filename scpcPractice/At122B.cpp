#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
string str;
int main() {
	int sol = 0;
	int length = 0;
	cin >> str;
	for (char ch : str) {
		if (ch == 'A' || ch == 'T' || ch == 'C' || ch == 'G') {
			length++;
			sol = max(length, sol);
		}
		else {
			length = 0;
		}
	}
	cout << sol << endl;
}