#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll fdiv(ll a, ll b) {
    assert(b > 0);
    return a >= 0 ? a / b : -((-a + b - 1) / b);
}
ll cdiv(ll a, ll b) {
    return -fdiv(-a, b);
}
constexpr ll INF = 1e17;
pair<int, ll> f(ll a, ll b) { // ax >= b
    if (a == 0) return {0, b <= 0 ? -INF : INF};
    else if (a > 0) return {0, cdiv(b, a)};
    return {1, fdiv(-b, -a)};
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, c, l;
    cin >> n >> c >> l;

    vector<pair<ll, ll>> a(n);
    for (auto &[x, v] : a) cin >> x >> v;

    a.emplace_back(0, 0);
    a.emplace_back(l, 0);
    n += 2;

    sort(a.begin(), a.end());
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);

    int L, R;
    for (int i = 0; i < n; i++) {
        if (a[i] == pair<ll, ll>{0, 0}) L = i;
        else if (a[i] == pair<ll, ll>{l, 0}) R = i;
    }

    vector<array<int, 3>> evt;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            auto [xi, vi] = a[i];
            auto [xj, vj] = a[j];
            if (vi > vj) {
                int t = (xj - xi) / (vi - vj) + 1;
                evt.push_back({t, i, j});
            }
        }
    }
    sort(evt.rbegin(), evt.rend());

    set<pair<ll, int>> ts[2];
    auto push = [&](int i) {
        if (idx[L] > i || i + 1 > idx[R]) return;
        auto [x1, v1] = a[i];
        auto [x2, v2] = a[i + 1];
        auto [dir, val] = f(v2 - v1, c - x2 + x1);
        ts[dir].emplace(val, i);
    };
    auto push2 = [&](int i) {
        push(i);
        push(i - 1);
    };

    auto pop = [&](int i) {
        if (idx[L] > i || i + 1 > idx[R]) return;
        auto [x1, v1] = a[i];
        auto [x2, v2] = a[i + 1];
        auto [dir, val] = f(v2 - v1, c - x2 + x1);
        ts[dir].erase({val, i});
    };
    auto pop2 = [&](int i) {
        pop(i);
        pop(i - 1);
    };

    for (int i = idx[L]; i < idx[R]; i++) push(i);

    int q;
    for (cin >> q; q--;) {
        int t;
        cin >> t;

        set<array<ll, 4>> s;
        set<int> poss;
        while (!evt.empty() && t >= evt.back()[0]) {
            auto [_, i, j] = evt.back();
            evt.pop_back();
            for (auto k : {i, j}) {
                auto [x, v] = a[idx[k]];
                s.insert({x + v * t, v, x, k});
                poss.insert(idx[k]);
                pop2(idx[k]);
            }
        }

        auto it = poss.begin();
        for (auto [_, v, x, i] : s) {
            idx[i] = *it++;
            a[idx[i]] = {x, v};
        }
        for (auto pos : poss) push2(pos);
        cout << "NY"[!ts[0].empty() && ts[0].begin()->first <= t || !ts[1].empty() && t <= prev(ts[1].end())->first] << "\n";
    }

    return 0;
}
