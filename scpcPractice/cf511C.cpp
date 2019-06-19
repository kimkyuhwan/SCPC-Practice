#include <bits/stdc++.h>
using namespace std;
#define MAX 4000
#define INF 1e9
int N;
int a[300010];
int ans=INF, another;
vector<int> prime;
bool isPrime[MAX+1];
map<int, int> mmap;
map<int, int> notChecked;
vector<vector<int> > vec;
void initPrime() {
	isPrime[2] = true;
	prime.push_back(2);
	for (int i = 3; i <= MAX; i += 2) {
		isPrime[i] = true;
	}
	for (int i = 3; i <= MAX; i += 2) {
		if (!isPrime[i]) continue;
		prime.push_back(i);
		for (int j = i * 3; j <= MAX; j += i) {
			isPrime[j] = false;
		}
	}


}


int main() {
	initPrime();
	vec.resize(prime.size(), vector<int>(32));
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf(" %d", &a[i]);
		mmap[a[i]]++;
		for (int j = 0; j < prime.size(); j++) {
			if (a[i] < prime[j]) break;
			int cnt = 0;
			while (a[i] % prime[j] == 0) {
				a[i] /= prime[j];
				vec[j][cnt++]++;
			}
		}
		if (a[i] != 1) {
			notChecked[a[i]]++;
		}
	}
	for (auto it = notChecked.begin(); it != notChecked.end(); it++) {
		int cnt = it->second;
		ans = min(ans, N - cnt);
	}

	for (int i = 0; i < prime.size(); i++) {
		for (int j = 0; j < 32; j++) {
			if (vec[i][j] == 0) continue;
			if (vec[i][j] == N) continue;
			ans = min(ans, N-vec[i][j]);
		}
	}
	if (mmap.size() == 1) puts("-1");
	else printf("%d\n", ans);
}