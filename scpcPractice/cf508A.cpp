#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int al[26];
int N, K;
char temp;
int main()
{
	scanf("%d %d", &N,&K);
	for (int i = 0; i < N; i++) {
		scanf(" %c", &temp);
		al[temp - 'A']++;
	}
	int maxx = 1000000;
	for (int i = 0; i < K; i++) {
		maxx = min(al[i], maxx);
	}
	printf("%d\n", maxx*K);
}