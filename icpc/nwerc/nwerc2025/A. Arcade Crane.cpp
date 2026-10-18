#include <bits/stdc++.h>
using namespace std;
using ll = long long;

using i5 = array<int, 5>;
vector<pair<int, int>> solve(i5 s) {
    auto f = [&](i5 cur, int i, int j) {
        i5 nxt{};
        for (int k = 0; k < 3; k++) nxt[j + k] = cur[i + k];
        int idx = 0;
        for (int k = 0; k < 5; k++) if (k < i || k > i + 2) {
            if (idx == j) idx = j + 3;
            nxt[idx++] = cur[k];
        }
        return nxt;
    };
    map<i5, tuple<int, int, i5>> p;
    vector<pair<int, int>> op;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) if (j != i) op.emplace_back(i, j);
    }

    queue<i5> q;
    q.emplace(s);
    p[s] = {-1, -1, {}};
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        for (auto [i, j] : op) {
            auto nxt = f(cur, i, j);
            if (!p.count(nxt)) {
                q.push(nxt);
                p[nxt] = {i, j, cur};
            }
        }
    }

    auto cur = s;
    sort(cur.begin(), cur.end());
    vector<pair<int, int>> res;
    while (cur != s) {
        auto [i, j, prv] = p[cur];
        res.emplace_back(i, j);
        cur = prv;
    }
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> v(n + 1);
    for (int i = 1; i <= n; i++) cin >> v[i];

    vector<pair<int, int>> ans;
    auto f = [&](int i, int j) {
        ans.emplace_back(i, j);
        vector<int> nv(n + 1);
        for (int k = 0; k < 3; k++) nv[j + k] = v[i + k];
        int idx = 0;
        for (int k = 0; k <= n; k++) if (k < i || k > i + 2) {
            nv[idx] = v[k];
            if (++idx == j) idx = j + 3;
        }
        swap(v, nv);
    };

    for (int i = 1; i <= n - 5; i++) {
        int idx = find(v.begin(), v.end(), i) - v.begin();
        if (idx == i) continue;

        if (idx + 2 <= n) f(idx, i);
        else { // idx > n - 2
            f(n - 2, n - 3);
            --i;
        }
    }

    array<int, 5> v2 = {v[n - 4], v[n - 3], v[n - 2], v[n - 1], v[n]};
    for (auto [i, j] : solve(v2)) ans.emplace_back(i + n - 4, j + n - 4);

    cout << ans.size() << "\n";
    for (auto [i, j] : ans) cout << i << " " << j << "\n";

    return 0;
}
