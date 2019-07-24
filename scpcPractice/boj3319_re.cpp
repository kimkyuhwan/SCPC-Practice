#include <bits/stdc++.h>

using namespace std;

#define ll long long

const int N = 1e5 + 15;

ll M[N], B[N];

struct convex {
	int sz;
	int id[N];

	double Cross(int a, int b) {
		if (a == b) {
			exit(0);
		}
		if (M[a] == M[b]) {
			exit(0);
		}

		return (double)(B[b] - B[a]) / (M[a] - M[b]);
	}



	int add(int myid) {
		int l = 0, r = sz - 1, mid;

		while (l<r) {

			mid = (l + r) / 2;

			if (Cross(id[mid], myid)<Cross(id[mid], id[mid + 1]))
				r = mid;
			else
				l = mid + 1;
		}

		return l + 1;
	}


	ll getval(ll x, int iid) {
		return B[iid] + x*M[iid];
	}

	ll query(ll x) {
		int l = 0, r = sz - 1, mid;
		while (l<r) {

			mid = (l + r) / 2;
			if (Cross(id[mid], id[mid + 1]) >= x)
				r = mid;
			else
				l = mid + 1;
		}
		return getval(x, id[l]);
	}
};
int a[N], b[N], w[N];
vector<int> adj[N];

int S[N], V[N];
convex con;

ll depth[N];


void dfs(int root, int p) {
	int u, i, id;

	int sz;
	vector<pair<ll, ll> >v;
	if (root == 1) {
		con.sz = 1;
		con.id[0] = 1;
	}
	else {
		ll depth = -M[root];
		ll z = con.query(V[root]) + S[root] + depth*V[root];
		B[root] = z;

		int pos = con.add(root);

		sz = con.sz;

		v.push_back(make_pair(pos, con.id[pos]));
		con.sz = pos + 1;
		con.id[pos] = root;
	}

	for (i = 0; i<adj[root].size(); ++i) {

		id = adj[root][i];

		u = a[id] ^ b[id] ^ root;

		if (u != p) {
			M[u] = M[root] - w[id];
			dfs(u, root);
		}
	}
	con.sz = sz;

	for (i = 0; i<v.size(); ++i) {
		int ind = v[i].first;
		con.id[ind] = v[i].second;
	}

}

int main() {
	int n, i;

	cin >> n;
	//for(i=0;i<N;++i)con.id[i] = 0;
	for (i = 0; i<n - 1; ++i) {
		scanf("%d%d%d", &a[i], &b[i], &w[i]);
		adj[a[i]].push_back(i);
		adj[b[i]].push_back(i);
	}
	for (i = 2; i <= n; ++i) {
		scanf("%d%d", &S[i], &V[i]);
	}
	dfs(1, 0);
	for (i = 2; i <= n; ++i)
		cout << B[i] << " ";
}