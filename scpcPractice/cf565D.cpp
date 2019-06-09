#include <bits/stdc++.h>
using namespace std;
#define INF 2750131
int isPrime[INF + 1];
int gg[INF + 1];
vector<int> prime;
int isVisited[INF + 1];
void initPrime() {
	int cnt = 1;
	isPrime[2] = cnt++;
	gg[2] = 1;
	prime.push_back(2);
	for (int i = 3; i <= INF; i+=2) isPrime[i] = 1;
	for (int i = 2; i <= INF; i += 2) gg[i] = i / 2;
	for (int i = 3; i <= INF; i+=2) {
		if (!isPrime[i]) continue;
		isPrime[i] = cnt++;
		gg[i] = 1;
		prime.push_back(i);
		for (int j = i * 3; j <= INF; j += i) {
			isPrime[j] = 0;
			if (gg[j] == 0) {
				gg[j] = j / i;
			}
		}
	}
}

int main() {
	initPrime();

	vector<int> vec;
	int N, val;
	scanf("%d", &N);
	N *= 2;
	for (int i = 0; i < N; i++) {
		scanf("%d", &val);
		vec.push_back(val);
		isVisited[val]++;
	}
	sort(vec.rbegin(), vec.rend());
	vector<int> ans;
	for (int here : vec) {
		if (isVisited[here]==0) continue;
		if (isPrime[here]) {
			if (here >= 200000) {
				continue;
			}
			else {
				if (isVisited[prime[here-1]]!=0) {
					ans.push_back(here);
					isVisited[here]--;;
					isVisited[prime[here-1]]--;
				}
			}
		}
		else {
			if (isVisited[gg[here]]!=0) {
				ans.push_back(here);
				isVisited[here]--;
				isVisited[gg[here]]--;
			}
		}
	}
	for (int i : ans) {
		printf("%d ", i);
	}
}