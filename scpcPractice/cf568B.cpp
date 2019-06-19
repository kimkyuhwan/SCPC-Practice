#include <bits/stdc++.h>
using namespace std;
int N;
char str[1000010];
char str2[1000010];
int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf(" %s ", str);
		scanf(" %s", str2);
		int a = strlen(str);
		int b = strlen(str2);
		bool flag = true;
		if (a > b) puts("NO");
		else {
			int j, k;
			if (str[0] != str2[0]) {
				flag = false;
			}
			else{
				for (j = 1, k = 1; k < b; k++) {
					j = min(a, j);
					if (str[j] == str2[k]) {
						j++;
					}
					else if(str[j-1] != str2[k]){
						flag = false;
						break;
					}
				}
				if (j != a) flag = false;
			}
			
			if (flag) puts("YES");
			else puts("NO");
		}
	}

}