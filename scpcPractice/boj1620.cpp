#include <bits/stdc++.h>
using namespace std;
int N, M;
map<string, int> nameToNumber;
map<int, string> numberToName;
char str[110];

int stringToInt(const string &str) {
	int ret = 0;
	for (int i = 0; i < str.size(); i++) {
		ret *= 10;
		ret += str[i] - '0';
	}
	return ret;
}


int main() {
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		scanf(" %s", str);
		nameToNumber[str] = i;
		numberToName[i] = str;
	}
	for (int i = 1; i <= M; i++) {
		scanf(" %s", str);
		if (str[0] >= '0' && str[0] <= '9') {
			printf("%s\n",numberToName[stringToInt(str)].c_str());
		}
		else {
			printf("%d\n", nameToNumber[str]);
		}
	}
}