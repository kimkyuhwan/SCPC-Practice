#include <bits/stdc++.h>
using namespace std;
int N;

vector<int> prime;
int isPrime[100010];

void initPrime() {
	int cnt = 1;
	for (int i = 2; i <= 100000; i++) {
		if (isPrime[i] != 0) continue;
		for (int j = i; j <= 100000; j += i) {
			isPrime[j] = cnt;
		}
		cnt++;
	}
}


int main(){
	initPrime();
	scanf("%d", &N);
	for (int i = 2; i <= N; i++) {
		printf("%d ", isPrime[i]);
	}
}