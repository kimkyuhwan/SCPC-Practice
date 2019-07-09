#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int N;
vector<ll> arr;
vector<bool> isPossible;
ll a, b, cnt, sum;
char input[50];
int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf(" %s", input);
		bool minus = false;
		a = 0, b = 0;
		int j = 0;
		if (input[0] == '-') {
			minus = true;
			j++;
		}
		bool aa = true;
		for (; j < strlen(input); j++) {
			if (input[j] == '.') {
				aa = false;
				continue;
			}
			if (aa) {
				a *= 10;
				a += input[j] - '0';
			}
			else {
				b *= 10;
				b += input[j] - '0';
			}
		}
		if (minus) a = -a;
		if (b != 0) {
			cnt++;
			isPossible.push_back(true);
			if (!minus) {
				arr.push_back(a);
			}
			else {
				arr.push_back(--a);
			}
		}
		else {
			isPossible.push_back(false);
			arr.push_back(a);
		}
		
		sum += a;
	}
	for (int i = 0; i < N && sum<0; i++) {
		if (!isPossible[i]) continue;
		arr[i]++;
		sum++;
	}
	for (int i = 0; i < N; i++) {
		printf("%d\n", arr[i]);
	}
	return 0;

}