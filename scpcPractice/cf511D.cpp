#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N, M, ans;
int main() {
	scanf("%lld %lld", &N, &M);
	if (N > M) swap(N, M);
	if (N == 3 && M == 3) {
		ans = 8;
	}
	else if (N >= 3 && M >= 3) {
		ans = N*M;
	}
	else if(N==1){
		ans = (M / 6) * 6;
		M %= 6;
		if (M == 4) {
			ans += 2;
		}
		else if(M==5){
			ans += 4;
		}
	}
	else if (N == 2) {
		if (M == 3) {
			ans = 4;
		}
		else if (M == 7) {
			ans = 12;
		}
		else if(M>=4){
			ans = N*M;
		}
	}
	ans = (ans)-(ans % 2 == 1);
	printf("%lld\n", ans);
}