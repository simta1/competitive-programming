#include <bits/stdc++.h>
using namespace std;
using ll = long long;

auto get_cartesian(const vector<int> &v) { // min // 0-based
    int n = v.size();
    vector<pair<int, int> > chd(n, {-1, -1});
    vector<int> s;
    for (int i = 0; i < n; i++) {
        while (!s.empty() && v[s.back()] > v[i]) {
            chd[i].first = s.back();
            s.pop_back();
        }
        if (!s.empty()) chd[s.back()].second = i;
        s.push_back(i);
    }
    return pair{s[0], chd}; // root, chd
}
// i의 왼쪽 직계 자식에서 오른쪽 방향으로만 이동하는 체인 위의 j에 대해 right_lt[j]=i
// i의 오른쪽 직계 자식에서 왼쪽 방향으로만 이동하는 체인 위의 j에 대해 left_le[j]=i

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<int> v(n);
    for (auto &e : v) cin >> e;

    auto [root, chd] = get_cartesian(v);

    vector<vector<ll>> dp(n);
    auto dfs = [&](auto &&dfs, int cur) -> void {
        dp[cur] = {0, 0};
        auto [l, r] = chd[cur];
        for (auto nxt : {l, r}) if (~nxt) {
            dfs(dfs, nxt);
            vector<ll> ndp(dp[cur].size() + dp[nxt].size() - 1);
            for (int i = 0; i < dp[cur].size(); i++) {
                for (int j = 0; j < dp[nxt].size(); j++) {
                    ndp[i + j] = max(ndp[i + j], dp[cur][i] + dp[nxt][j] + ll(v[nxt] - v[cur]) * j * (m - j));
                }
            }
            swap(dp[cur], ndp);
        }
    };
    dfs(dfs, root);

    cout << dp[root][m];

    return 0;
}
