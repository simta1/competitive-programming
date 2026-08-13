#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, m;
    cin >> m >> n;

    vector<int> v(n);
    for (auto &e : v) cin >> e;

    vector<bitset<5000>> rdj(n);
    for (int i = 0; i < n; i++) rdj[i].set();

    for (int i = 0; i < m; i++) {
        vector<pair<int, int>> r(n);
        for (int i = 0; i < n; i++) {
            cin >> r[i].first;
            r[i].second = i;
        }
        sort(r.begin(), r.end());
        bitset<5000> cur;
        for (int i = 0, j = 1; i < n; i = j) {
            while (j < n && r[i].first == r[j].first) ++j;
            for (int k = i; k < j; k++) rdj[r[k].second] &= cur;
            for (int k = i; k < j; k++) cur[r[k].second] = 1;
        }
    }

    vector<int> indeg(n);
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (rdj[j][i]) {
                adj[i].push_back(j);
                ++indeg[j];
            }
        }
    }

    queue<int> q;
    vector<ll> dp(n);
    for (int i = 0; i < n; i++) if (!indeg[i]) {
        q.push(i);
        dp[i] = v[i];
    }

    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        for (auto nxt : adj[cur]) {
            dp[nxt] = max(dp[nxt], dp[cur] + v[nxt]);
            if (--indeg[nxt] == 0) q.push(nxt);
        }
    }

    cout << *max_element(dp.begin(), dp.end());

    return 0;
}
