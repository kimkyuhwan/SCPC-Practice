#include <bits/stdc++.h>
using namespace std;
int q, n;
int arr[510];
int main() {
	scanf("%d", &q);
	while (q--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &arr[i]);
			arr[i + n] = arr[i];
		}
		bool sol = false;
		for (int i = 0; i < n; i++) {
			if (arr[i] == 1) {
				bool isPossbile = true;
				for (int j = i, cnt = 1; j < n*2 &&cnt <= n; j++, cnt++) {
					if (arr[j] != cnt) {
						isPossbile = false;
						break;
					}
				}
				if (isPossbile) {
					sol = true;
					break;
				}
			}
		} 
		for (int i = 2*n-1; i >=n; i--) {
			if (arr[i] == 1) {
				bool isPossbile = true;
				for (int j = i, cnt = 1; j >=0 && cnt <= n; j--, cnt++) {
					if (arr[j] != cnt) {
						isPossbile = false;
						break;
					}
				}
				if (isPossbile) {
					sol = true;
					break;
				}
			}
		}
		if (sol) puts("YES");
		else puts("NO");
	}
}