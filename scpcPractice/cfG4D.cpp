#include <bits/stdc++.h>
using namespace std;
vector<int> prime;
bool isPrime[2010];
int n;
vector<pair<int, int> > ans;
void initPrime() {
	isPrime[2] = true;
	prime.push_back(2);
	for (int i = 3; i <= 2000; i += 2) {
		isPrime[i] = true;
	}
	for (int i = 3; i <= 2000; i += 2) {
		if (!isPrime[i]) continue;
		prime.push_back(i);
		for (int j = i * 3; j <= 2000; j += i) {
			isPrime[j] = false;
		}
	}
}


int main() {
	initPrime();
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int a = i % n;
		int b = (i + 1) % n;
		ans.push_back({ a + 1,b + 1 });
	}
	int idx = lower_bound(prime.begin(), prime.end(), n)-prime.begin();
	int pr = prime[idx];
	int mid = n / 2;
	for (int i = 0; i < n / 2; i++) {
		if (pr - ans.size() == 0) break;
		int a = i%n;
		int b = (i + mid) % n;
		ans.push_back({ a+1,b+1 });
	}
	printf("%d\n", ans.size());
	for (int i = 0; i < ans.size(); i++) {
		printf("%d %d\n", ans[i].first, ans[i].second);
	}

}