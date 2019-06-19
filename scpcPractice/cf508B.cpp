#include <bits/stdc++.h>
using namespace std;
int N;
typedef long long ll;
vector<int> A, B;
ll sumA, sumB;
ll gcd(ll a, ll b) {
	if (a < b) swap(a, b);
	if (a%b == 0) return b;
	return gcd(b, a%b);
}
int main() {
	scanf("%d", &N);
	if (N <=2) {
		puts("No");
		return 0;
	}
	for (int i = 1; i <= N; i++) {
		if (i % 2 == 0) {
			A.push_back(i);
			sumA += i;
		}
		else {
			B.push_back(i);
			sumB += i;
		}
	}
	puts("Yes");
	printf("%d ", A.size());
	for (int i : A) {
		printf("%d ", i);
	}
	puts("");
	printf("%d ", B.size());
	for (int i : B) {
		printf("%d ", i);
	}
	puts("");
}