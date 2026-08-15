#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct DSU {
	vector<int> p, sz;
	DSU(int n) : p(n + 1), sz(n + 1, 1) {
		iota(p.begin(), p.end(), 0);
        fill(sz.begin(), sz.end(), 1);
	}
	int find(int a) {
		while (p[a] != a) a = p[a] = p[p[a]];
		return a;
	}
	void merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        p[a] = b;
        sz[b] += sz[a];
	}
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        DSU dsu(n);
        for (int i = 1; i <= n; i++) {
            int x;
            cin >> x;
            dsu.merge(i, x);
        }

        int ans = 0;
        vector<bool> visited(n + 1);
        for (int i = 0; i < n; i++) {
            int d;
            cin >> d;
            d = dsu.find(d);
            if (!visited[d]) {
                visited[d] = 1;
                ans += dsu.sz[d];
            }
            cout << ans << " ";
        }
        cout << "\n";




        
    }

    return 0;
}
