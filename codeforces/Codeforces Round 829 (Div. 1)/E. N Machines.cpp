#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, b, p, m;
    cin >> n >> b >> p >> m;

    vector<pair<char, int>> v;
    map<int, vector<int>> mp;
    int tot_mul = 1;
    for (int i = 0; i < n; i++) {
        char op;
        int a;
        cin >> op >> a;
        if (op == '*' && a == 1) continue;

        v.emplace_back(op, a);
        if (op == '*') {
            mp[a].push_back(v.size() - 1);
            tot_mul *= a;
        }
    }

    n = v.size();
    vector<vector<int>> muls;
    for (auto &[a, idxes] : mp) muls.push_back(idxes);

    vector<tuple<int, vector<int>, vector<int>>> pluss;
    int pi = -1;
    for (int i = 0; i <= n; i++) if (i == n || v[i].first == '*') {
        vector<int> cur;
        for (int k = pi + 1; k < i; k++) cur.push_back(v[k].second);
        sort(cur.begin(), cur.end());
        auto sfs = cur;
        for (int i = int(sfs.size()) - 2; i >= 0; i--) sfs[i] += sfs[i + 1];
        pluss.emplace_back(pi, cur, sfs);
        pi = i;
    }
    assert(pluss.size() <= 31);

    vector<bool> moved(n);
    ll ans = 0;
    auto dfs = [&](auto &&dfs, int idx, int cnt) -> void {
        if (idx == muls.size()) {
            ll res = tot_mul;
            int mul = 1;
            for (auto &[mulidx, vals, sfs] : pluss) {
                if (mulidx >= 0 && !moved[mulidx]) mul *= v[mulidx].second;
                res += tot_mul / mul * ll(sfs.empty() ? 0 : sfs[0]);
            }
            int have = (b - m * cnt) / p;

            auto count = [&](ll mn) {
                int cnt = 0;
                int mul = 1;
                for (auto &[mulidx, vals, sfs] : pluss) {
                    if (mulidx >= 0 && !moved[mulidx]) mul *= v[mulidx].second;
                    ll coef = tot_mul - tot_mul / mul;
                    // a * coef >= mn
                    // a >= (mn + coef - 1) / coef
                    if (!coef) continue;
                    cnt += vals.end() - lower_bound(vals.begin(), vals.end(), (mn + coef - 1) / coef);
                }
                return cnt;
            };

            ll lo = 0, hi = 1e18;
            while (lo + 1 < hi) {
                ll mid = lo + hi >> 1;
                if (count(mid) >= have) lo = mid;
                else hi = mid;
            }

            ll mn = lo;
            mul = 1;
            int used = 0;
            for (auto &[mulidx, vals, sfs] : pluss) {
                if (mulidx >= 0 && !moved[mulidx]) mul *= v[mulidx].second;
                ll coef = tot_mul - tot_mul / mul;
                // a * coef > mn
                // a >= (mn) / coef
                if (!coef) continue;
                auto it = upper_bound(vals.begin(), vals.end(), mn / coef);
                if (it != vals.end()) {
                    used += vals.end() - it;
                    res += sfs[it - vals.begin()] * coef;
                }
            }
            ans = max(ans, res + (have - used) * mn);
            return;
        }

        dfs(dfs, idx + 1, cnt);
        for (int i = 1; i <= muls[idx].size(); i++) {
            moved[muls[idx][i - 1]] = 1;
            if (cnt + i <= b / m) dfs(dfs, idx + 1, cnt + i);
        }

        for (auto i : muls[idx]) moved[i] = 0;
    };
    dfs(dfs, 0, 0);

    cout << ans;

    return 0;
}
