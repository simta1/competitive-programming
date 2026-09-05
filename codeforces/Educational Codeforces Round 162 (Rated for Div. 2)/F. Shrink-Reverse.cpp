#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename Container>
auto get_sa(const Container &st) { // O(N logN)
    int n = st.size();
    if (n == 1) return pair{vector{0}, vector{0}};
    assert(n > 0);
    int m = *max_element(st.begin(), st.end());
    vector<int> sa(n), x(n + 1), y(n + 1), cnt(max(n, m) + 1);
    for (int i = 0; i < n; i++) assert(st[i] > 0);
    for (int i = 0; i < n; i++) ++cnt[x[i] = st[i]];
    for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--) sa[--cnt[x[i]]] = i;
    for (int len = 1, p = 1; p < n; len <<= 1, m = p) {
        int idx = 0;
        for (int i = n - len; i < n; i++) y[idx++] = i;
        for (int i = 0; i < n; i++) if (sa[i] >= len) y[idx++] = sa[i] - len;
        fill(cnt.begin(), cnt.begin() + m + 1, 0);
        for (int i = 0; i < n; i++) ++cnt[x[y[i]]];
        for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) sa[--cnt[x[y[i]]]] = y[i];
        swap(x, y);
        x[sa[0]] = p = 1;
        for (int i = 1; i < n; i++) {
            int a = sa[i - 1], b = sa[i];
            x[b] = y[a] == y[b] && y[a + len] == y[b + len] ? p : ++p;
        }
    }
    x.resize(n);
    for (auto &e : x) --e;
    return pair{sa, x}; // rank=x
}
template <typename Container>
vector<int> get_lcp(const Container &st, const vector<int> &sa, const vector<int> &rank) { // O(N)
    int n = st.size();
    assert(n >= 1);
    vector<int> lcp(n - 1);
    for (int i = 0, h = 0; i < n; ++i, h -= !!h) if (rank[i]) {
        for (int j = sa[rank[i] - 1]; j + h < n && i + h < n && st[j + h] == st[i + h];) ++h;
        lcp[rank[i] - 1] = h;
    }
    return lcp;
} // lcp[i]: sa[i], sa[i + 1]의 최장 공통 접두사 // lcp.size() = n-1

constexpr ll MOD = 1e9 + 7;
ll f(const string &st) {
    ll res = 0;
    for (auto ch : st) {
        res = res << 1 | (ch == '1');
        res %= MOD;
    }
    return res;
}

string solve(int n, int k, string st) {
    int z = n - 1;
    for (int i = 0; i < n && k; i++) if (st[i] == '1') {
        while (z >= 0 && st[z] == '1') --z;
        if (i < z) {
            swap(st[i], st[z]);
            --k;
        }
        else break;
    }
    return st;
}

string solve2(int n, int k, string st) {
    reverse(st.begin(), st.end());

    vector<int> pfs(n);
    for (int i = 0; i < n; i++) pfs[i] = st[i] == '1';
    for (int i = 1; i < n; i++) pfs[i] += pfs[i - 1];
    int c1 = pfs.back();

    auto [sa, rank] = get_sa(st);
    auto lcp = get_lcp(st, sa, rank);

    constexpr int INF = 1e8;
    array<int, 3> mn = {INF, INF, -1}; // {len, rank, l}
    vector<pair<int, int>> v;
    for (int l = 0, r = 0; l < n; l++) {
        if (r - l + 1 < c1) r = l - 1 + c1;
        int x = l ? pfs[l - 1] : 0;
        while (r < n && pfs[r] < x + c1 - k + 1) ++r;
        if (r == n) break;

        array<int, 3> cur = {r - l + 1, rank[l], l};
        mn = min(mn, cur);
    }

    auto [len, _, l] = mn;
    string res = st.substr(l, len);
    int r = l + len - 1;
    int need = c1 - (pfs[r] - (l ? pfs[l - 1] : 0));
    for (int i = res.size() - 1; need && i >= 0; i--) if (res[i] == '0') {
        res[i] = '1';
        --need;
    }
    return string(n - res.size(), '0') + res;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    string st;
    cin >> st;

    cout << f(min(solve(n, k, st), solve2(n, k, st)));

    return 0;
}
