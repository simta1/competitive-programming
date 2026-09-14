#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    constexpr ll MOD = 998'244'353;
    constexpr ll P = 998'244'353;
    constexpr int N = 15e4;
    static ll inv[N + 2] = {1, 1};
    for (int i = 2; i <= N + 1; ++i) inv[i] = inv[P % i] * (P - P / i) % P;
    static ll cat[N + 1] = {1, 1};
    for (int i = 2; i <= N; ++i) cat[i] = cat[i - 1] * (4 * i - 2) % P * inv[i + 1] % P;
    // C0 = 1, C1 = 1, C2 = 2, C3 = 5
    // C_n = 2nCn / (n + 1) = C_{n - 1} * (4n - 2) / (n + 1)

    int TC;
    for (cin >> TC; TC--;) {
        int n, k;
        cin >> n >> k;

        mt19937_64 rng;
        vector<ull> imos(n + 1);
        while (k--) {
            int l, r;
            cin >> l >> r;
            ull h = rng();
            imos[l] ^= h;
            if (r + 1 <= n) imos[r + 1] ^= h;
        }

        map<ull, int> mp;
        for (int i = 1; i <= n; i++) {
            imos[i] ^= imos[i - 1];
            ++mp[imos[i]];
        }

        ll ans = 1;
        for (auto [hash, cnt] : mp) {
            if (cnt & 1) {
                ans = 0;
                break;
            }
            else ans = ans * cat[cnt >> 1] % MOD;
        }
        cout << ans << "\n";
    }

    return 0;
}
