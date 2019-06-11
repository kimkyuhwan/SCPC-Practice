#include <bits/stdc++.h>
using namespace std;

char isVowel(char ch) {
	return ch == 'a' || ch == 'e' || ch == 'o' || ch == 'u' || ch == 'i';
}

pair<int, char> getStringProperties(string str) {
	int cntVowel = 0;
	char lastVowel = ' ';
	for (int i = 0; i < str.size(); i++) {
		if (isVowel(str[i])) {
			cntVowel++;
			lastVowel = str[i];
		}
	}
	return{ cntVowel,lastVowel };
}

int N;
string str[100010];
map<pair<int, char>, vector<int> > mmap;
vector<pair<int, int> > ans;
map<int, vector<int> > cntMap;
vector<bool> used;
vector<vector<int> > remainFirst;
vector<pair<int,int> > remainSecond, remainFirstTemp;

int main() {
	cin >> N;
	used.resize(N);
	for (int i = 0; i < N; i++) {
		cin >> str[i];
		auto properties= getStringProperties(str[i]);
		mmap[properties].push_back(i);
		cntMap[properties.first].push_back(i);
	}
	int lastLength = 0;
	int remainFirstCnt = 0;
	for (auto it = mmap.begin(); it != mmap.end(); it++) {
		if (lastLength != it->first.first) {
			lastLength = it->first.first;
			remainFirst.push_back(vector<int>());
		}
		int i = 1;
		int cnt = it->second.size();
		for (; i < cnt; i+=2) {
			remainSecond.push_back({ it->second[i - 1],it->second[i] });
		}
		if (i == cnt) {
			remainFirst.back().push_back(it->second.back());
		}
	}
	for (int i = 0; i < remainFirst.size(); i++) {
		remainFirstCnt += remainFirst[i].size() / 2;
		for (int j = 1; j < remainFirst[i].size(); j += 2) {
			remainFirstTemp.push_back({ remainFirst[i][j - 1], remainFirst[i][j] });
		}
	}
	int ans = min(remainFirstTemp.size(), remainSecond.size());
	if (remainFirstTemp.size() < remainSecond.size()) {
		ans += (remainSecond.size() - remainFirstTemp.size()) / 2;
	}
	cout << ans << endl;
	for (int i = 0; i < remainFirstTemp.size() && i<remainSecond.size(); i++) {
		cout << str[remainFirstTemp[i].first] << " " << str[remainSecond[i].first] << endl;
		cout << str[remainFirstTemp[i].second] << " " << str[remainSecond[i].second] << endl;
	}
	if (remainFirstTemp.size() < remainSecond.size()) {
		int cnt = remainSecond.size() - remainFirstTemp.size();
		for (int i = 1; i < cnt; i+=2) {
			cout << str[remainSecond[i + remainFirstTemp.size() - 1].first] << " " << str[remainSecond[i + remainFirstTemp.size()].first] << endl;
			cout << str[remainSecond[i + remainFirstTemp.size() - 1].second] << " " << str[remainSecond[i + remainFirstTemp.size()].second] << endl;
		}
	}
}