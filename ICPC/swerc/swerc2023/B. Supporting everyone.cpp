#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

	vector<vector<int>> adj(n);

	for (int i = 0; i < n; i++) {
        int k;
        for (cin >> k; k--;) {
			int j;
			cin >> j;
			adj[i].push_back(j - 1);
        }
    }

	vector<int> ml(n, -1), mr(m, -1), vr(m);
	int t = 1;
	auto dfs = [&](auto &&dfs, int l) -> bool {
		for (auto r : adj[l]) if (vr[r] != t) {
			vr[r] = t;
			if (!~mr[r] || dfs(dfs, mr[r])) {
				ml[l] = r;
				mr[r] = l;
				return true;
			}
		}
		return false;
	};

	int ans = 0;
	for (int i = 0; i < n; ++i, ++t) ans += dfs(dfs, i);
	cout << ans;
    
    return 0;
}
