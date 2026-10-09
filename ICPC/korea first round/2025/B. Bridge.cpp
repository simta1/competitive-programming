#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = double;
using P = pair<ld, ld>;

ld dist(P &a, P &b) {
    ld dx = a.first - b.first;
    ld dy = a.second - b.second;
    return sqrt(dx * dx + dy * dy);
}

P interpol(P &a, P &b, ld y) {
    auto [x1, y1] = a;
    auto [x2, y2] = b;
    if (x1 == x2) return {x1, y};
    return {(x2 - x1) / (y2 - y1) * (y - y1) + x1, y};
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<pair<ld, ld>> v(n);
    for (auto &[x, y] : v) cin >> x >> y;

    vector<ld> pref(n), suf(n);
    for (int i = 1; i < n; i++) pref[i] = pref[i - 1] + dist(v[i - 1], v[i]);
    for (int i = n - 2; i >= 0; i--) suf[i] = suf[i + 1] + dist(v[i], v[i + 1]);

    auto solve = [&](int j, int i, ld lo, ld hi) {
        if (lo == hi) return 9e18;
        auto f = [&](ld y) {
            P p1 = interpol(v[j], v[j + 1], y);
            P p2 = interpol(v[i], v[i + 1], y);
            ld bridge = p2.first - p1.first;
            ld d1 = dist(v[j], p1);
            ld d2 = dist(p2, v[i + 1]);
            ld cycle = pref[i + 1] - pref[j] - d1 - d2 + bridge;
            return max(pref[j] + d1 + bridge + d2 + suf[i + 1], max(pref[j] + d1, suf[i + 1] + d2) + cycle / 2);
        };

        for (int _ = 100; _--;) {
            ld p = (2 * lo + hi) / 3;
            ld q = (lo + 2 * hi) / 3;
            if (f(p) > f(q)) lo = p;
            else hi = q;
        }
        return f(lo);
    };

    ld ans = pref[n - 1];
    stack<int> s;
    for (int i = 0; i + 1 < n; i++) {
        if (v[i].second > v[i + 1].second) {
            s.push(i);
        }
        else if (v[i].second < v[i + 1].second){
            ld mn = v[i].second, mx = v[i + 1].second;
            while (!s.empty()) {
                if (v[s.top() + 1].second > v[i + 1].second) break;
                int j = s.top();
                ans = min(ans, solve(j, i, mn, min(mx, v[j].second)));
                mn = v[j].second;

                if (v[s.top()].second <= v[i + 1].second) s.pop();
                else break;
            }
        }
    }
    cout << fixed << setprecision(12) << ans;

    return 0;
}
