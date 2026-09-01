#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> p(n), c(n);
    for (auto &e : p) cin >> e;
    for (auto &e : c) cin >> e;

    constexpr int N = 1'000'000;
    static int c_at_p[N + 1], p_at_c[N + 1];
    constexpr int INF = 1e9;
    for (int i = 0; i <= N; i++) c_at_p[i] = p_at_c[i] = INF;
    int mn = INF;
    for (int i = 0; i < n; i++) {
        c_at_p[p[i]] = min(c_at_p[p[i]], c[i]);
        p_at_c[c[i]] = min(p_at_c[c[i]], p[i]);
        mn = min(mn, c[i] + p[i]);
    }

    static int c_pref[N + 1], c_suf[N + 1], p_pref[N + 1], p_suf[N + 1];
    c_pref[0] = c_at_p[0];
    p_pref[0] = p_at_c[0];
    for (int i = 1; i <= N; i++) {
        c_pref[i] = min(c_at_p[i], c_pref[i - 1]);
        p_pref[i] = min(p_at_c[i], p_pref[i - 1]);
    }
    c_suf[N] = c_at_p[N];
    p_suf[N] = p_at_c[N];
    for (int i = N - 1; i >= 0; i--) {
        c_suf[i] = min(c_at_p[i], c_suf[i + 1]);
        p_suf[i] = min(p_at_c[i], p_suf[i + 1]);
    }

    auto f = [&](int x, int a, int d) {
        if (x == INF) return INF;
        if (x < a) return 0;
        if (x <= a + d) return x;
        return a + d;
    };

    int m;
    cin >> m;

    vector<int> tp(m), tc(m), d(m);
    for (auto &e : tp) cin >> e;
    for (auto &e : tc) cin >> e;
    for (auto &e : d) cin >> e;

    for (int i = 0; i < m; i++) {
        int a = tp[i], b = tc[i];
        int ans = mn;
        if (a) ans = min(ans, f(c_pref[a - 1], b, d[i]));
        if (a + d[i] + 1 <= N) ans = min(ans, a + d[i] + f(c_suf[a + d[i] + 1], b, d[i]));
        if (b) ans = min(ans, f(p_pref[b - 1], a, d[i]));
        if (b + d[i] + 1 <= N) ans = min(ans, b + d[i] + f(p_suf[b + d[i] + 1], a, d[i]));
        cout << ans << "\n";
    }

    return 0;
}
