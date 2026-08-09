#include <bits/stdc++.h>
using namespace std;
using ll = long long;

namespace Poly { // FFT
template <typename real_t>
void fft(vector<complex<real_t>> &a) {
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
}
template <typename real_t>
void ifft(vector<complex<real_t>> &a) {
    reverse(a.begin() + 1, a.end());
    fft(a);
    for (auto &e : a) e /= real_t(a.size());
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
    fft(in);
    for (auto &x : in) x *= x;
    for (int i = 0; i < n; i++) out[i] = in[-i & (n - 1)] - conj(in[i]);
	fft(out);
    vector<ll> res(need);
    for (int i = 0; i < res.size(); i++) res[i] = llround(imag(out[i]) / (4 * n));
	return res;
}
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<vector<int>> adj(n + 1);
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        auto bfs = [&](int s) {
            vector<int> dist(n + 1, -1);
            vector<int> p(n + 1, -1);
            queue<int> q;
            q.push(s);
            dist[s] = 0;
            while (!q.empty()) {
                auto cur = q.front();
                q.pop();
                for (auto nxt : adj[cur]) if (!~dist[nxt]) {
                    dist[nxt] = dist[cur] + 1;
                    p[nxt] = cur;
                    q.push(nxt);
                }
            }
            return pair{dist, p};
        };

        auto [d1, p1] = bfs(1);
        int a = max_element(d1.begin(), d1.end()) - d1.begin();
        auto [da, pa] = bfs(a);
        int b = max_element(da.begin(), da.end()) - da.begin();
        int D = da[b];
        vector<bool> ans(D + 1);

        auto f = [&](int root, int rp, int d) {
            vector<int> dep(n + 1), dp(n + 1, -1), res(d + 1);
            res[d] = 1;
            auto mkt = [&](auto &&mkt, int cur, int par) -> void {
                for (auto nxt : adj[cur]) if (nxt != par) {
                    dep[nxt] = dep[cur] + 1;
                    mkt(mkt, nxt, cur);
                    dp[cur] = max(dp[cur], dp[nxt]);
                }
                if (!~dp[cur]) dp[cur] = dep[cur];
            };
            mkt(mkt, root, rp);

            auto dfs = [&](auto &&dfs, int cur, int par) -> void {
                int cnt = 0;
                for (auto nxt : adj[cur]) if (nxt != par) {
                    if (dp[nxt] == d) ++cnt;
                }
                if (cnt >= 2) res[dep[cur]] = 1;
                for (auto nxt : adj[cur]) if (nxt != par) dfs(dfs, nxt, cur);
            };
            dfs(dfs, root, rp);
            return res;
        };

        vector<int> path;
        for (int cur = b; ~cur; cur = pa[cur]) path.push_back(cur);
        assert(D & 1);
        int c1 = path[D / 2], c2 = path[D / 2 + 1];
        auto len1 = f(c1, c2, D / 2);
        auto len2 = f(c2, c1, D / 2);
        auto tmp = Poly::multiply<double>(len1, len2);
        for (int i = 0; i < tmp.size(); i++) if (tmp[i]) ans[i + 1] = 1;

        int ansc = 0;
        for (int i = 1; i <= D; i++) ansc += ans[i];
        cout << ansc << " ";
        for (int i = 1; i <= D; i++) if (ans[i]) cout << i << " ";
        cout << "\n";
    }

    return 0;
}
