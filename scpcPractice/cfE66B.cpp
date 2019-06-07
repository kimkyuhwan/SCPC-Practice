#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define INF (1LL<<32)-1
int l, N;
ll sol = 0;

string str;
vector<ll> vec;
stack<int> st;
ll getMulti() {
	ll ret = 1;
	for (int i = 0; i < vec.size(); i++) {
		ret *= vec[i];
		if (ret > INF) {
			return -1;
		}
	}
	return ret;
}


int main() {
	bool isOver = false;
	cin >> l;
	for (int i = 0;  i < l; i++) {
		cin >> str;
		if (str == "add") {
			ll mul = getMulti();
			if (isOver) continue;
			if (mul == -1) {
				isOver = true;
			}
			else{
				sol+=mul;
			}
			if (sol > INF) {
				isOver = true;
			}
		}
		else if (str == "for") {
			cin >> N;
			if (N != 1) {
				vec.push_back(N);
			}
			st.push(N);
		}
		else if (str == "end") {
			if(!vec.empty() && st.top()!=1)
				vec.pop_back();
			st.pop();
		}
	}
	if (isOver) {
		puts("OVERFLOW!!!");
		return 0;
	}
	cout << sol << endl;

}