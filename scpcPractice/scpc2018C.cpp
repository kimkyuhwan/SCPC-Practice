#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50010;
typedef long long ll;
typedef pair<pair<int, int>, int> piii;
int N, T;
struct vector2 {
	double x, y;
	//생성자
	vector2() : vector2(0, 0) {}
	vector2(double _x, double _y) {
		x = _x, y = _y;
	}
	//외적
	double cross(const vector2& other) const {
		return x*other.y - y*other.x;
	}

	/* 연산자 오버로딩을 통해 실제 벡터의 연산을 구현합니다. */

	//벡터의 실수배
	vector2 operator * (double r) const {
		return vector2(x*r, y*r);
	}
	//벡터의 덧셈
	vector2 operator + (vector2 other) const {
		return vector2(x + other.x, y + other.y);
	}
	//벡터의 뺄셈
	vector2 operator - (vector2 other) const {
		return vector2(x - other.x, y - other.y);
	}
	//두 벡터의 비교
	bool operator == (vector2 other) const {
		return x == other.x && y == other.y;
	}
	bool operator < (vector2 other) const {
		return x < other.x && y < other.y;
	}
};


pair<vector2,vector2> makeVectors(vector2 &a, vector2 &b) {
	return { a,b};
}
vector2 pp[MAXN];
vector2 nn[MAXN];
piii pa[MAXN * 2];
piii pb[MAXN * 2];

double ccw(vector2 a, vector2 b) {
	return a.cross(b);
}
//점 p를 기준으로 벡터 b가 벡터 a의 반시계 방향이면 양수, 시계방향이면 음수, 평행이면 0을 반환 한다.
double ccw(vector2 p, vector2 a, vector2 b) {
	return ccw(a - p, b - p);
}

bool sementIntersects(vector2 a, vector2 b, vector2 c, vector2 d) {
	double ab = ccw(a, b, c)*ccw(a, b, d);
	double cd = ccw(c, d, a)*ccw(c, d, b);
	//두 선분이 한 직선에 위에 있거나 끝점이 겹치는 경우
	if (ab == 0 && cd == 0) {
		if (b < a) swap(a, b);
		if (d < c) swap(c, d);
		return !(b< c || d <a);
	}
	return ab <= 0 && cd <= 0;
}

pair<int, int> solution(vector<int> a) {
	vector<pair<vector2, vector2> > vecs;
	int ret = 0;
	for (int i = 0; i < N; i++) {
		vecs.push_back(makeVectors(pp[i],nn[a[i]]));
	}
	int last = (1 << N);
	int maxState = 0;
	for (int state = 1; state < last; state++) {
		int sum = 0;
		for (int i = 0; i < vecs.size(); i++) {
			if ((state & (1 << i)) == 0) continue;
			bool ans = true;
			for (int j = 0; j < vecs.size(); j++) {
				if (i == j) continue;
				if ((state & (1 << j)) == 0) continue;
				if (sementIntersects(vecs[i].first,vecs[i].second, vecs[j].first,vecs[j].second)) {
					ans = false;
					break;
				}
			}
			if (ans) sum++;
		}
		if (ret < sum) {
			maxState = state;
			ret = sum;
		}
	}
	return{ ret,maxState };
}


int main() {
	scanf("%d", &T);
	for (int testcase = 1; testcase <= T; testcase++) {
		scanf("%d", &N);
		int ans = 0;
		vector<int> connects;
		printf("Case #%d\n", testcase);


		if (N > 7) {
			for (int i = 0; i < N * 2; i++) {
				scanf(" %d %d", &pa[i].first.second, &pa[i].first.first);
				pa[i].second = i + 1;
				if (i >= N) {
					pa[i].second = -((i + 1) - N);
				}
				pb[i] = pa[i];
				swap(pb[i].first.first, pb[i].first.second);
			}
			vector<pair<int, int> > sol, sol2;

			sort(pa, pa + 2 * N);
			sort(pb, pb + 2 * N);
			for (int i = 0; i < N * 2 - 1; i++) {
				if (pa[i].second * pa[i + 1].second < 0) {
					int a = pa[i].second;
					int b = pa[i + 1].second;
					if (a < b) swap(a, b);
					sol.push_back({ a,-b });
					i++;
				}
			}
			for (int i = 0; i < N * 2 - 1; i++) {
				if (pb[i].second * pb[i + 1].second < 0) {
					int a = pb[i].second;
					int b = pb[i + 1].second;
					if (a < b) swap(a, b);
					sol2.push_back({ a,-b });
					i++;
				}
			}
			if (sol.size() > sol2.size()) {
				printf("%d\n", sol.size());
				for (int i = 0; i < sol.size(); i++) {
					printf("%d %d\n", sol[i].first, sol[i].second);
				}
			}
			else {
				printf("%d\n", sol2.size());
				for (int i = 0; i < sol2.size(); i++) {
					printf("%d %d\n", sol2[i].first, sol2[i].second);
				}
			}
		}
		else {
			for (int i = 0; i < N; i++) {
				scanf("%lf %lf", &pp[i].x, &pp[i].y);
			}
			for (int i = 0; i < N; i++) {
				scanf("%lf %lf", &nn[i].x, &nn[i].y);
			}
			vector<int> arr(N);
			int maxx = 0;
			for (int i = 0; i < N; i++) arr[i] = i;
			do {
				pair<int, int> ans = solution(arr);
				if (maxx < ans.first) {
					maxx = ans.first;
					int state = ans.second;
					connects.clear();
					for (int i = 0; i < N; i++) {
						if (state & (1 << i)) {
							connects.push_back(arr[i]);
						}
					}
				}
			} while (next_permutation(arr.begin(), arr.end()));
			printf("%d\n", maxx);
			for (int i = 0; i < connects.size(); i++) {
				printf("%d %d\n", i + 1, connects[i] + 1);
			}
		}
	}
}