#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
string str;
int N, Q;
int l, r;
int psum[200010];
int main() {
	cin >> N >> Q;
	cin >> str;

	for (int i = 1; i < str.size(); i++) {
		int val = 0;
		if (str[i] == 'C' && str[i - 1] == 'A') {
			val = 1;
		}
		psum[i+1] = psum[i]+val;
	}


	for (int i = 0; i < Q; i++) {
		cin >> l >> r;
		cout << psum[r] - psum[l] << endl;
	}
}