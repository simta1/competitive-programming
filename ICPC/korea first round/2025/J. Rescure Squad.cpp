#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].first;
        v[i].second = i;
    }

    vector<int> a(n);
    sort(v.rbegin(), v.rend());
    for (int i = 0; i < n; i++) a[v[i].second] = i;

    vector<bitset<1000>> adj(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[a[u]][a[v]] = adj[a[v]][a[u]] = 1;
    }

    int ans = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) if (i != j) {
            auto bs = adj[i] & adj[j];
            if (bs.count() < 2) continue;
            int k = bs._Find_first();
            int l = bs._Find_next(k);
            ans = max(ans, v[i].first + v[j].first + v[k].first + v[l].first);
        }
    }

    cout << ans << "\n";

    return 0;
}
