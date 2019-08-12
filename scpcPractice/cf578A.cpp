#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int N;
string str = "0000000000";
char cmd;

void insertLeft() {
	string nstr = str;
	if (str[0] == '0') {
		nstr[0] = '1';
		str = nstr;
		return;
	}
	for (int i = 0; i < 10; i++) {
		if (str[i] == '1') {
			nstr[i + 1] = '1';
		}
		else {
			break;
		}
	}
	str = nstr;
	return;
}


void insertRight() {
	string nstr = str;
	if (str[9] == '0') {
		nstr[9] = '1';
		str = nstr;
		return;
	}
	for (int i = 9; i >=0; i--) {
		if (str[i] == '1') {
			nstr[i - 1] = '1';
		}
		else {
			break;
		}
	}
	str = nstr;
	return;
}


int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf(" %c", &cmd);
		if (cmd == 'L') {
			insertLeft();
		}
		else if (cmd == 'R') {
			insertRight();
		}
		else if(cmd>='0' && cmd<='9'){
			str[cmd - '0'] = '0';
		}
	}
	cout << str << endl;

}