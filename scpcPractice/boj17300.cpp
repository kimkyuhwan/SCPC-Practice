#include <bits/stdc++.h>
using namespace std;
int dy[16] = {-1,-1,-1,0,0,1,1,1,-2,-1,-2,-1,2,1,2,1};
int dx[16] = {-1,0,1,-1,1,-1,0,1,1,2,-1,-2,1,2,-1,-2};
int L, A, cur;
bool visited[10];
bool isPossible=true;

pair<int, int> getXY(int num) {
	--num;
	return{ num / 3,num % 3 };
}


int getPosition(int y, int x) {
	return (y * 3 + x)+1;
}

bool isPossiblePostion(int y, int x) {
	return y >= 0 && y < 3 && x >= 0 && x < 3;
}

bool canGo(int A, int B) {
	if (visited[B]) return false;
	queue<int> q;
	q.push(A);
	vector<int> dist(10,100);
	dist[A] = 0;
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		pair<int, int> cur = getXY(here);
		for (int k = 0; k < 16; k++) {
			int nextY = cur.first + dy[k];
			int nextX = cur.second + dx[k];
			if (isPossiblePostion(nextY,nextX)) {
				int there = getPosition(nextY, nextX);
				while (isPossiblePostion(nextY, nextX) && visited[there]) {
					nextY += dy[k];
					nextX += dx[k];
					there = getPosition(nextY, nextX);
				}
				if (!isPossiblePostion(nextY, nextX)) {
					continue;
				}
				int thereDist = dist[here] + 1;
				if (dist[there]>thereDist) {
					q.push(there);
					dist[there] = thereDist;
				}
			}
		}
	}
	return dist[B] == 1;
}
int main()
{
	scanf("%d", &L);
	scanf("%d", &A);
	cur = A;
	visited[cur] = true;
	for (int i = 1; i < L; i++) {
		scanf("%d", &A);
		if (canGo(cur, A)) {
			visited[A] = true;
		}
		else {
			isPossible = false;
		}
		cur = A;
	}
	if (isPossible) puts("YES");
	else puts("NO");
	return 0;
}