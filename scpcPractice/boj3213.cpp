#include <bits/stdc++.h>
using namespace std;
int N, ans;
string str;
int pizza[3];
int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> str;
		if (str == "1/4") { pizza[0]++; }
		else if (str == "1/2") { pizza[1]++; }
		else {pizza[2]++;}
	}
	ans = pizza[2];
	pizza[0] -= pizza[2];
	ans += pizza[1] / 2;
	pizza[1] %= 2;
	if (pizza[0] > 0) {
		if (pizza[1] > 0) {
			pizza[0] -= 2;
			pizza[1]--;
			ans++;
		}
		if(pizza[0]>0) ans += pizza[0] / 4 + (pizza[0] % 4 != 0);
	}
	ans += (pizza[1] % 2) != 0;
	printf("%d\n", ans);
}