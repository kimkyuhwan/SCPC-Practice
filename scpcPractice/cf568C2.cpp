#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int cnt[110];
int N, M, val;
int v[200010];
int main(){
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		ll sum = M;
		scanf("%d", &val);
		sum -= val;
		int ccnt = 0;
		for (int j = 1; j <= 100 && sum; j++) {
			if (j*cnt[j] > sum) {
				int aa = sum / j;
				sum -= j *aa;
				ccnt += aa;
				break;
			}
			else {
				sum -= j*cnt[j];
				ccnt += cnt[j];
			}
		}
		printf("%d ", i - ccnt);
		cnt[val]++;
	}
}