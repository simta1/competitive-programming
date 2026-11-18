#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct DSU {
	vector<int> p;
	DSU(int n) : p(n) {
		iota(p.begin(), p.end(), 0);
	}
	int find(int a) {
		while (a != p[a]) a = p[a] = p[p[a]];
		return a;
	}
	void merge(int a, int b) {
		p[find(a)] = find(b);
	}
};

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, k, l;
	cin >> n >> k >> l;

	DSU dsu(n + 1);
	while (k--) {
		int u, v;
		cin >> u >> v;
		dsu.merge(u, v);
	}

	DSU dsu2(n + 1);
	while (l--) {
		int u, v;
		cin >> u >> v;
		dsu2.merge(u, v);
	}

	vector<pair<int, int>> v;
	for (int i = 1; i <= n; i++) v.emplace_back(dsu.find(i), dsu2.find(i));

	sort(v.begin(), v.end());
	
	for (int i = 1; i <= n; i++) {
		pair<int, int> p = {dsu.find(i), dsu2.find(i)};
		cout << upper_bound(v.begin(), v.end(), p) - lower_bound(v.begin(), v.end(), p) << " ";
	}

	return 0;
}
