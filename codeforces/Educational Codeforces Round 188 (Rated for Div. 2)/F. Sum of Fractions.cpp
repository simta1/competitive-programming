#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll MOD = 998'244'353;
ll binpow(ll a, ll n) {
    ll res = 1;
    for (; n; n >>= 1) {
        if (n & 1) res = res * a % MOD;
        a = a * a % MOD;
    }
    return res;
}
ll modInv(ll a) {
    return binpow(a, MOD - 2);
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<int> v(n);
    for (auto &e : v) cin >> e;

    stack<int> s;
    vector<int> left_le(n, -1), right_lt(n, n);
    for (int i = 0; i < n; i++) {
        while (!s.empty() && v[s.top()] > v[i]) {
            right_lt[s.top()] = i;
            s.pop();
        }
        if (!s.empty()) left_le[i] = s.top();
        s.push(i);
    }

    vector<pair<int, ll>> a(n + 1);
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        int l = left_le[i];
        int r = right_lt[i];
        ll cnt = (i - l) * ll(r - i) % MOD;
        a[i + 1] = {v[i], cnt};

        sum += (ll(i + 1) * (n - i) - cnt) % MOD * modInv(v[i]);
        sum %= MOD;
    }

    sort(a.begin() + 1, a.end());
    vector<ll> pfs1(n + 1), pfs2(n + 1);
    for (int i = 1; i <= n; i++) {
        auto [b, c] = a[i];
        pfs1[i] = pfs1[i - 1];
        pfs2[i] = pfs2[i - 1];
        pfs1[i] += (-b + 2) * c;
        pfs1[i] %= MOD;
        pfs2[i] += c;
        if (pfs2[i] >= MOD) pfs2[i] -= MOD;
    }

    vector<ll> sfs(n + 2);
    for (int i = n; i >= 1; i--) {
        auto [b, c] = a[i];
        sfs[i] = sfs[i + 1];
        sfs[i] += c * modInv(b);
        sfs[i] %= MOD;
    }

    int idx = 0;
    while (m--) {
        int k;
        cin >> k;

        while (idx + 1 <= n && a[idx + 1].first <= k) ++idx;

        ll ans = sum;
        ans += pfs1[idx] + k * pfs2[idx];
        ans += sfs[idx + 1] * (k + 1);
        ans %= MOD;

        if (ans < 0) ans += MOD;
        cout << ans << "\n";
    }

    return 0;
}
