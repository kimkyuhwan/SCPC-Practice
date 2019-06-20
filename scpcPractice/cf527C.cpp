#include <bits/stdc++.h>
using namespace std;
int N, inp;
string str[300], ans;
vector<string> vec[110];
map<string, int> mmap;
map<string, int> rea;
set<string> st;

bool isPossible(string A) {
	map<string, int> temp;
	for (int i = 1; i < N; i++) {
		string PP = A.substr(0, i);
		temp[PP]++;
		string SS = A.substr(N - i, N);
		temp[SS]++;
	}
	for (auto it = rea.begin(); it != rea.end(); it++) {
		if (temp[it->first] != it->second) return false;
	}
	return true;
}

int main(){
	cin >> N;
	inp = 2 * N - 2;
	for (int i = 0; i < inp; i++) {
		cin >> str[i];
		vec[str[i].length()].push_back(str[i]);
		rea[str[i]]++;
	}
	for (int i = 0; i < 2 && ans == ""; i++) {
		for (int j = 0; j < 2 && ans == ""; j++) {
			string sel = vec[1][i] + vec[N - 1][j];
			if (isPossible(sel)) {
				ans = sel;
			}
		}
	}
	for (int i = 0; i < 2 && ans == ""; i++) {
		for (int j = 0; j < 2 && ans == ""; j++) {
			string sel =  vec[N - 1][i] + vec[1][j];
			if (isPossible(sel)) {
				ans = sel;
			}
		}
	}
	for (int i = 1; i < N; i++) {
		string PP = ans.substr(0, i);
		mmap[PP]++;
		string SS = ans.substr(N-i,N);
		mmap[SS]--;
	}
	for (int i = 0; i < inp; i++) {
		if (mmap[str[i]] == 0) {
			printf("P");
			mmap[str[i]]--;
		}
		else if (mmap[str[i]] < 0) {
			printf("S");
		}
		else if (mmap[str[i]] > 0) {
			printf("P");
		}
	}
	puts("");
}