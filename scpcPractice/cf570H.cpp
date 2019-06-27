#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int ans;
int n, k, cnt, turn;
set<string> st;
string str;
map<ll, ll> mmap;
int main() {
	cin >> n >> k;
	cin >> str;
	k--;
	mmap[str.size()]++;

	
	if (k > 0) {
		puts("-1");
		return 0;
	}
	printf("%d\n", ans);
}