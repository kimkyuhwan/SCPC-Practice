#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int N;
char str[100010];
deque<char> A, B;

bool comp(string a, string b) {
	if (a.size() == b.size()) {
		for (int i = 0; i < a.size(); i++) {
			if (a[i] == b[i]) continue;
			return a[i] < b[i];
		}
		return false;
	}
	return a.size() < b.size();
}

string makeDeque(int r) {
	string a;
	string b;
	for (int i = 0; i < N; i++) {
		if (i <= r) {
			a.push_back(str[i]);
		}
		else {
			b.push_back(str[i]);
		}
	}
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	int N = a.size();
	int M = b.size();
	string ret(max(N, M) + 1, '0');
	if (N < M) {
		for (int i = 0; i < M - N; i++) a.push_back('0');
	}
	else {
		for (int i = 0; i < N - M; i++) b.push_back('0');
	}
	int maxx = max(N, M);
	for (int i = 0; i < maxx; i++) {
		int aVal = a[i] - '0';
		int bVal = b[i] - '0';
		int sum = aVal + bVal + ret[i];
		if (sum > '9') {
			sum -= '0';
			int up = sum / 10;
			int remain = sum % 10;
			ret[i] = remain + '0';
			ret[i + 1] = up + '0';
		}
		else {
			ret[i] = sum;
		}
	}
	while (ret.back() == '0') ret.pop_back();
	reverse(ret.begin(), ret.end());
	return ret;
}

int main() {
	scanf("%d", &N);
	scanf(" %s", str);
	int l = 0, r;
	int preR = -1;
	for (r = 0; r < N; r++) {
		if (str[r + 1] == '0') {
			continue;
		}
		if (r + 1 > N - 1 - r) {
			break;
		}
		preR = r;
	}
	string AA = makeDeque(r);
	string BB;
	if (preR != -1) {
		BB = makeDeque(preR);
	}
	if (!BB.empty() && !comp(AA, BB)) {
		for (int i = 0; i < BB.size(); i++) {
			printf("%c", BB[i]);
		}
	}
	else {
		for (int i = 0; i < AA.size(); i++) {
			printf("%c", AA[i]);
		}
	}
}