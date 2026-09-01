#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct DSU {
	vector<int> p;
	DSU(int n) : p(n) {
		iota(p.begin(), p.end(), 0);
	}
	int find(int a) {
		return a == p[a] ? a : p[a] = find(p[a]);
	}
	void merge(int a, int b) {
		p[find(a)] = find(b);
	}
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, c;
    cin >> n >> c;

    vector<array<int, 3>> edges;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int w;
            cin >> w;
            if (w) edges.push_back({w, i, j});
        }
    }
    sort(edges.begin(), edges.end());

    ll ans = 9e18;
    for (int mask = 0; mask < (1 << n); mask++) {
        DSU dsu(n);
        ll cur = __builtin_popcount(mask) * c;
        int cnt = n;
        for (auto [w, u, v] : edges) {
            if ((mask >> u & 1) || (mask >> v & 1)) {
                if (dsu.find(u) == dsu.find(v)) continue;
                --cnt;
                dsu.merge(u, v);
                cur += w;
            }
        }
        if (cnt == 1) ans = min(ans, cur);
    }

    cout << ans;

    return 0;
}
