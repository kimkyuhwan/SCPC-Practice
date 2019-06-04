#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAXX (1<<18)
ll n, x;
bool visited[MAXX];
vector<ll> arr;
int main() {
	cin >> n >> x;
	ll last = (1 << n);
	visited[x] = true;
	for (int i = 1; i <last; i++) {
		if (visited[i]) continue;
		visited[i] = true, visited[i^x] = true;
		arr.push_back(i);
	}

	cout << arr.size()<<endl;
	int res = 0;
	for (int i = 0; i < arr.size(); i++) {
		res ^= arr[i];
		cout << res << " ";
		res = arr[i];
	}

}