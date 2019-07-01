#include <bits/stdc++.h>
using namespace std;
int T, N;
int A[300010];
int B[300010];
bool visited[300010];
int mmap[300010];
int main()
{
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		scanf("%d", &N);
		int cnt = 0;
		bool ans = true;
		for (int j = 0; j < N; j++) {
			scanf("%d", &A[j]);
			visited[A[j]] = false;
			mmap[A[j]] = 0;
		}
		for (int j = 0; j < N; j++) {
			scanf("%d", &B[j]);
			visited[B[j]] = false;
			mmap[B[j]] = 0;
		}
		int first = -1, last = -1;
		for (int j = 0; j < N; j++) {
			mmap[A[j]]++;
			mmap[B[j]]--;
			if (mmap[A[j]] != 0 && !visited[A[j]]) {
				visited[A[j]] = true;
				cnt++;
			}
			else if(mmap[A[j]]==0 && visited[A[j]]){
				visited[A[j]] = false;
				cnt--;
			}

			if (mmap[B[j]] != 0 && !visited[B[j]]) {
				visited[B[j]] = true;
				cnt++;
			}
			else if (mmap[B[j]] == 0 && visited[B[j]]) {
				visited[B[j]] = false;
				cnt--;
			}


			if (cnt>0) {
				if (first == -1) {
					first = j;
				}
			}
			else if(first!=-1){
				last = j;
				sort(A + first, A + last + 1);
				first = -1;
			}
		}
		
		for (int j = 0; j < N; j++) {
			if (A[j] != B[j]) {
				ans = false;
				break;
			}
		}
		if (ans) puts("YES");
		else puts("NO");
		
	}
}