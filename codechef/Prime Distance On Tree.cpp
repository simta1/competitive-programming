#include <bits/stdc++.h>
using namespace std;
using ll = long long;

namespace Poly { // FFT
template <typename real_t>
void fft(vector<complex<real_t>> &a, bool inv) {
    using cpx = complex<real_t>;
    int n = a.size(), L = __lg(n);
    static vector<complex<long double>> R(2, 1);
    static vector<cpx> rt(2, 1);
    for (static int k = 2; k < n; k *= 2) {
        R.resize(n); rt.resize(n);
        auto x = polar(1.0L, acos(-1.0L) / k);
        for (int i = k; i < 2 * k; i++) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
    }
    vector<int> rev(n);
    for (int i = 0; i < n; i++) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    for (int i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                auto x = (real_t *)&rt[j+k], y = (real_t *)&a[i+j+k];
                cpx z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);
                // cpx z = rt[j + k] * a[i + j + k];
                a[i + j + k] = a[i + j] - z;
                a[i + j] += z;
            }
        }
    }
    if (inv) {
        reverse(a.begin() + 1, a.end());
        for (auto &e : a) e /= real_t(a.size());
    }
}
template <typename real_t, typename T>
vector<ll> multiply(const vector<T> &A, const vector<T> &B) {
    assert(!A.empty() && !B.empty());
    using cpx = complex<real_t>;
    int need = A.size() + B.size() - 1;
    int n = 1;
    while (n < need) n <<= 1;
    vector<cpx> in(n), out(n);
    for (int i = 0; i < A.size(); i++) in[i] = A[i];
    for (int i = 0; i < B.size(); i++) in[i].imag(B[i]);
    fft(in, false);
    for (auto &x : in) x *= x;
    for (int i = 0; i < n; i++) out[i] = in[-i & (n - 1)] - conj(in[i]);
    fft(out, false);
    vector<ll> res(need);
    for (int i = 0; i < res.size(); i++) res[i] = llround(imag(out[i]) / (4 * n));
    return res;
}
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    constexpr int N = 5e4;
    static int lpf[N + 1];
    vector<int> primes;
    for (int i = 2; i <= N; i++) {
        if (!lpf[i]) {
            lpf[i] = i;
            primes.push_back(i);
        }
        for (auto p : primes) {
            if (p > N / i) break;
            lpf[i * p] = p;
            if (i % p == 0) break;
        }
    }

    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

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

    vector<int> dep(n + 1, -1);
    vector<int> dirt;
    auto bfs = [&](int cur) {
        queue<int> q;
        q.push(cur);
        dep[cur] = 1;
        vector<int> cnt = {0, 1};
        while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            dirt.push_back(cur);
            for (auto nxt : adj[cur]) if (!rm[nxt] && !~dep[nxt]) {
                dep[nxt] = dep[cur] + 1;
                if (dep[nxt] == cnt.size()) cnt.resize(dep[nxt] + 1);
                ++cnt[dep[nxt]];
                q.push(nxt);
            }
        }
        return cnt;
    };

    ll ans = 0;
    auto f = [&](const vector<int> &cnt, int add) {
        auto c2 = Poly::multiply<double>(cnt, cnt);
        for (auto p : primes) {
            if (p >= c2.size()) break;
            ans += add * c2[p];
        }
    };

    auto dnc = [&](auto &&dnc, int cur) -> void {
        int tot = get_sz(get_sz, cur, -1);
        int ct = get_ct(get_ct, cur, -1, tot);
        rm[ct] = 1;
        vector<int> sum = {1};
        for (auto nxt : adj[ct]) if (!rm[nxt]) {
            auto cnt = bfs(nxt);
            f(cnt, -1);
            if (sum.size() < cnt.size()) sum.resize(cnt.size());
            for (int i = 0; i < cnt.size(); i++) sum[i] += cnt[i];
        }
        f(sum, 1);
        for (auto x : dirt) dep[x] = -1;
        dirt.clear();
        for (auto nxt : adj[ct]) if (!rm[nxt]) dnc(dnc, nxt);
    };
    dnc(dnc, 1);

    cout << fixed << setprecision(12) << double(ans) / n / (n - 1);

    return 0;
}
