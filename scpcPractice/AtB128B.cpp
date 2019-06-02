#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N, P;
string S;
vector<int> vec;
map < string, vector<pair<int, int> > > mmap;
int main() {
	cin >> N;
	for (int i = 1; i <= N; i++) {	
		cin >> S >> P;
		mmap[S].push_back(make_pair(P, i));
	}
	for (auto it = mmap.begin(); it != mmap.end(); it++) {
		sort(it->second.rbegin(), it->second.rend());
	}
	for (auto it = mmap.begin(); it != mmap.end(); it++) {
		for (pair<int, int> item : it->second) {
			cout << item.second << endl;
		}
	}
	return 0;
}