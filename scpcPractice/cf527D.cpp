#include <bits/stdc++.h>
using namespace std;
int N;
vector<int> arr;
int a, b, cnt, sum;
int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d.%d", &a, &b);
		if (b != 0) {
			cnt++;
		}
		else if (a > 0) {
			arr.push_back(a);
		}
		else {
			arr.push_back(--a);
		}
		sum += a;
	}
	for (int i = 0; i < N && sum<0; i++) {
		arr[i]++;
		printf("%d\n", arr[i]);
	}
	return 0;
	
}