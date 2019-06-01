#include <cstdio>
#include <algorithm>
using namespace std;
int b, r, s;

int main() {
	scanf("%d", &b);
	for (int testcase = 1; testcase <= b; testcase++) {
		scanf("%d", &r);
		int ans = 0;
		int sum = 0;
		int start=1, end=1;
		pair<int, int> sol = { 0,0 };
		for (int i = 1; i < r; i++) {
			scanf("%d", &s);
			end=i+1;
			sum += s;
			if (sum < 0) {
				sum = 0;
				start = i + 1;
			}
			if (ans < sum || (ans==sum && ((sol.second-sol.first)<end-start))) {
				sol.first = start;
				sol.second = end;
				ans = sum;
			}
		}
		if (sol.first != 0) {
			printf("The nicest part of route %d is between stops %d and %d\n", testcase,sol.first,sol.second);
		}
		else {
			printf("Route %d has no nice parts\n",testcase);
		}
	}
}