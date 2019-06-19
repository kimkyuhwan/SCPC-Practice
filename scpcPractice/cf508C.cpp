#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int N;
vector<int> A, B;
int a, b;
ll sumA, sumB;
int main() {
	scanf("%d", &N);
	A.resize(N), B.resize(N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &A[i]);
	}
	sort(A.rbegin(), A.rend());
	for (int i = 0; i < N; i++) {
		scanf("%d", &B[i]);
	}
	sort(B.rbegin(), B.rend());

	for (int i = 0; i < N; i++) {
		if (a == N) {
			b++;
		}
		else if (b == N) {
			sumA += A[a++];
		}
		else if (A[a] > B[b]) {
			sumA += A[a++];
		}
		else if(A[a]==B[b]){
			sumA += A[a++];
		}
		else {
			b++;
		}

		if (b == N) {
			a++;
		}
		else if (a == N) {
			sumB += B[b++];
		}
		else if (A[a] < B[b]) {
			sumB += B[b++];
		}
		else if (A[a] == B[b]) {
			sumB += B[b++];
		}
		else {
			a++;
		}
	}
	printf("%lld\n", sumA - sumB);
}