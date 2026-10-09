#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr ll MOD = 998'244'353;
void add(ll &a, ll b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

namespace Poly { // NTT
template <ll p> ll binpow(ll a, ll n) { // (MOD-1)^2<=INT64_MAX
    ll res = 1;
    for (; n; n >>= 1) {
        if (n & 1) res = res * a % p;
        a = a * a % p;
    }
    return res;
}
template <ll p, ll primitiveRoot>
void ntt(vector<ll> &a, bool inv) {
    int n = a.size(), L = __lg(n);
    static vector<ll> rt(2, 1);
    for (static int k = 2, s = 2; k < n; k <<= 1, ++s) {
        rt.resize(n);
        ll z[2] = {1, binpow<p>(primitiveRoot, p >> s)};
        for (int i = k; i < 2 * k; i++) rt[i] = rt[i >> 1] * z[i & 1] % p;
    }
    vector<int> rev(n);
    for (int i = 0; i < n; i++) rev[i] = (rev[i >> 1] | ((i & 1) << L)) >> 1;
    for (int i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                ll u = a[i + j], v = a[i + j + k] * rt[j + k] % p;
                a[i + j] = u + v < p ? u + v : u + v - p;
                a[i + j + k] = u - v >= 0 ? u - v : u - v + p;
            }
        }
    }
    if (inv) {
        reverse(a.begin() + 1, a.end());
        ll invN = binpow<p>(n, p - 2);
        for (auto &e : a) e = e * invN % p;
    }
}
template <ll p, ll primitiveRoot, typename T>
vector<ll> multiplyMod(const vector<T> &A, const vector<T> &B) {
    assert(!A.empty() && !B.empty());
    int need = A.size() + B.size() - 1;
    int n = 1;
    while (n < need) n <<= 1;
    assert(n <= ((p - 1) & -(p - 1))); // assert(n <= 2^b)
    vector<ll> a(n), b(n);
    for (int i = 0; i < A.size(); i++) {
        a[i] = A[i];
        // a[i] = A[i] % p;
        // if (a[i] < 0) a[i] += p;
    }
    for (int i = 0; i < B.size(); i++) {
        b[i] = B[i];
        // b[i] = B[i] % p;
        // if (b[i] < 0) b[i] += p;
    }
    ntt<p, primitiveRoot>(a, false);
    ntt<p, primitiveRoot>(b, false);
    for (int i = 0; i < n; i++) a[i] = a[i] * b[i] % p;
    ntt<p, primitiveRoot>(a, true);
    a.resize(need);
    return a;
}
// | p = a*2^b+1   | a   | b  | 2^b       | g |
// | ------------- | --- | -- | --------- | - |
// | 104'857'601   | 25  | 22 | 4194304   | 3 |
// | 167'772'161   | 5   | 25 | 33554432  | 3 |
// | 469'762'049   | 7   | 26 | 67108864  | 3 |
// | 998'244'353   | 119 | 23 | 8388608   | 3 |
// | 1'004'535'809 | 479 | 21 | 2097152   | 3 |
// | 1'012'924'417 | 483 | 21 | 2097152   | 5 |
// | 2'281'701'377 | 17  | 27 | 134217728 | 3 |
// | 2'483'027'969 | 37  | 26 | 67108864  | 3 |
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> tsz(n + 1, 1), p(n + 1, 1);
    auto mkt = [&](auto &&mkt, int cur, int par) -> int {
        for (auto nxt : adj[cur]) if (nxt != par) {
            p[nxt] = cur;
            tsz[cur] += mkt(mkt, nxt, cur);
        }
        return tsz[cur];
    };
    mkt(mkt, 1, -1);
    auto getCompSize = [&](int u, int v) { // u-v자르고 u쪽 크기
        if (v == p[u]) return tsz[u];
        return n - tsz[v];
    };
    vector<ll> sqsum(n + 1);
    for (int i = 1; i <= n; i++) {
        for (auto j : adj[i]) {
            ll x = getCompSize(j, i);
            sqsum[i] += x * x;
        }
    }
    auto f = [&](int u, int v) {
        ll x = getCompSize(u, v);
        ll y = n - x;
        return x * x - (sqsum[u] - y * y);
    };

    vector<int> sz(n + 1);
    vector<bool> rm(n + 1);
    auto get_sz = [&](auto &&get_sz, int cur, int par) -> int {
        sz[cur] = 1;
        for (auto nxt : adj[cur]) if (nxt != par && !rm[nxt]) {
            sz[cur] += get_sz(get_sz, nxt, cur);
        }
        return sz[cur];
    };
    auto get_ct = [&](auto &&get_ct, int cur, int par, int tot) -> int {
        for (auto nxt : adj[cur]) if (nxt != par && !rm[nxt]) {
            if (sz[nxt] * 2 > tot) return get_ct(get_ct, nxt, cur, tot);
        }
        return cur;
    };

    vector<int> dep(n + 1);
    auto dfs = [&](auto &&dfs, int cur, int par, vector<ll> &res) -> void {
        for (auto nxt : adj[cur]) if (nxt != par && !rm[nxt]) {
            dep[nxt] = dep[cur] + 1;
            dfs(dfs, nxt, cur, res);
        }
        if (res.size() <= dep[cur]) res.resize(dep[cur] + 1);
        res[dep[cur]] += f(cur, par);
        res[dep[cur]] %= MOD;
    };

    vector<ll> ans(n + 1);
    auto dnc = [&](auto &&dnc, int cur) -> void {
        int tot = get_sz(get_sz, cur, -1);
        int ct = get_ct(get_ct, cur, -1, tot);
        rm[ct] = 1;
        dep[ct] = 0;
        vector<tuple<unsigned int, vector<ll>, int>> tmp;
        for (auto nxt : adj[ct]) if (!rm[nxt]) {
            vector<ll> cnt;
            dep[nxt] = 1;
            dfs(dfs, nxt, ct, cnt);
            tmp.emplace_back(cnt.size(), cnt, nxt);
        }
        sort(tmp.begin(), tmp.end());
        vector<ll> sum(1);
        for (auto [_, cnt, nxt] : tmp) {
            sum[0] = f(ct, nxt) % MOD;
            auto mul = Poly::multiplyMod<MOD, 3>(sum, cnt);
            for (int i = 1; i < mul.size(); i++) add(ans[i], mul[i]);

            if (sum.size() < cnt.size()) sum.resize(cnt.size());
            for (int i = 1; i < cnt.size(); i++) add(sum[i], cnt[i]);
        }

        for (auto nxt : adj[ct]) if (!rm[nxt]) dnc(dnc, nxt);
    };
    dnc(dnc, 1);

    for (int i = 1; i < n; i++) cout << ans[i] << " ";

    return 0;
}
