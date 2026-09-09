#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<int> cnt(n + 1);
    while (m--) {
        int u, v;
        cin >> u >> v;
        if (u > v) swap(u, v);
        ++cnt[u];
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) ans += cnt[i] == 0;

    int q;
    for (cin >> q; q--;) {
        int op;
        cin >> op;
        if (op == 1) {
            int u, v;
            cin >> u >> v;
            if (u > v) swap(u, v);
            if (++cnt[u] == 1) --ans;
        }
        else if (op == 2) {
            int u, v;
            cin >> u >> v;
            if (u > v) swap(u, v);
            if (--cnt[u] == 0) ++ans;
        }
        else {
            cout << ans << "\n";
        }
    }

    return 0;
}
