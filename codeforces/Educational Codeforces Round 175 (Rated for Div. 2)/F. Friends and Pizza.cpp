#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void sos(ll a[]) {
    for (int i = 0; i < 20; i++) {
        for (int mask = 0; mask < (1 << 20); mask++) {
            if (mask >> i & 1) a[mask] += a[mask ^ (1 << i)];
        }
    }
}

void sos_inv(ll a[]) {
    for (int i = 0; i < 20; i++) {
        for (int mask = 0; mask < (1 << 20); mask++) {
            if (mask >> i & 1) a[mask] -= a[mask ^ (1 << i)];
        }
    }
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    static int cnt[1 << 20];
    while (m--) {
        string st;
        cin >> st;

        int mask = 0;
        for (auto ch : st) mask |= 1 << ch - 'A';
        ++cnt[mask];
    }

    vector<int> v(n);
    for (auto &e : v) cin >> e;

    int odd = 0;
    for (int i = 0; i < n; i++) if (v[i] & 1) odd |= 1 << i;

    static ll f[21][1 << 20];
    for (int mask = 0; mask < (1 << n); mask++) {
        f[__builtin_popcount(odd & mask)][mask] += cnt[mask];
    }

    for (int i = 0; i <= n; i++) sos(f[i]);

    static ll g[21][1 << 20];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; i + j <= n; j++) {
            for (int mask = 0; mask < (1 << n); mask++) {
                g[i + j][mask] += f[i][mask] * f[j][mask];
            }
        }
    }

    for (int i = 0; i <= n; i++) sos_inv(g[i]);
    // g[k][mask] : 합집합이 mask이고 교집합의 크기가 k - mask인 경우의 수
    // |A| + |B| = |A U B| + |A & B|

    int sum = accumulate(v.begin(), v.end(), 0);
    vector<ll> ans(sum + 1);
    for (int mask = 0; mask <= (1 << n); mask++) {
        int val = 0;
        for (int i = 0; i < n; i++) {
            if (~mask >> i & 1) val += v[i];
        }
        ans[val] += g[__builtin_popcount(mask & odd)][mask];
        if ((mask & odd) == 0) ans[val] -= cnt[mask];
    }

    for (auto e : ans) cout << e / 2 << " ";

    return 0;
}
