#include <bits/stdc++.h>
using namespace std;
using ll = long long;

tuple<ll, ll, ll> egcd(ll a, ll b) { // ax + by = gcd(a, b)
    if (b == 0) return {1, 0, a};
    auto [x, y, g] = egcd(b, a % b);
    return {y, x - (a / b) * y, g};
}
ll modInv(ll a, ll b) {
    auto [x, y, g] = egcd(a, b);
    return g != 1 ? -1 : (x + b) % b;
} // modInv(n, MOD)

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    constexpr ll MOD = 1e9 + 7;
    constexpr int N = 200'005;
    static ll fac[N + 1] = {1}, facInv[N + 1]{};
    for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % MOD;
    facInv[N] = modInv(fac[N], MOD);
    for (int i = N - 1; i >= 0; i--) facInv[i] = facInv[i + 1] * (i + 1) % MOD;
    auto nCr = [&](int n, int r) {
        return fac[n] * facInv[r] % MOD * facInv[n - r] % MOD;
    };

    int n, k;
    cin >> n >> k;

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if (k & 1) cout << 1;
    else {
        ll sum = 0;
        int half = k / 2;
        vector<int> sz(n + 1, 1);
        auto dfs = [&](auto &&dfs, int cur, int par) -> void {
            for (auto nxt : adj[cur]) if (nxt != par) {
                dfs(dfs, nxt, cur);
                sz[cur] += sz[nxt];
            }
            int a = sz[cur], b = n - sz[cur];
            if (a >= half && b >= half) {
                sum += nCr(a, half) * nCr(b, half);
                sum %= MOD;
            }
        };
        dfs(dfs, 1, -1);

        cout << (sum * modInv(nCr(n, k), MOD) + 1) % MOD << "\n";
    }

    return 0;
}
