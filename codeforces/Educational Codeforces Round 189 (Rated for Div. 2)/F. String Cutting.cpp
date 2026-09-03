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

template <typename T, const T& (*op)(const T&, const T&)>
struct RMQ {
	vector<vector<T> > ac; // ac[i][j] = op(v[j:j+2^i))
	RMQ(const vector<T> &v) : ac(1, v) { // O(N logN)
		for (int i = 1, len = 1; len * 2 <= v.size(); ++i, len *= 2) {
			ac.emplace_back(v.size() - len * 2 + 1);
			for (int j = 0; j < ac[i].size(); j++) ac[i][j] = op(ac[i - 1][j], ac[i - 1][j + len]);
		}
	}
	T query(int a, int b) const { // 0-based // op[a:b]의 op() 누적값 // O(1)
		assert(0 <= a && a <= b && b < ac[0].size());
		int i = __lg(b - a + 1);
		return op(ac[i][a], ac[i][b - (1 << i) + 1]);
	}
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, l, k;
        string st;
        cin >> n >> l >> k >> st;

        if (ll(l) * k <= n) {
            cout << "YES\n";

            if (k == 1) cout << st << "\n";
            else {
                auto [sa, rank] = get_sa(st);
                auto lcp = get_lcp(st, sa, rank);
                const RMQ<int, min> rmq(lcp);
                auto cmp = [&](int i, int j, int i2, int j2) { // st[i:j] < st[i2:j2]
                    auto [l, r] = minmax(rank[i], rank[i2]);
                    int len = rmq.query(l, r - 1);
                    if (len >= min(j - i + 1, j2 - i2 + 1)) return j - i < j2 - i2;
                    return rank[i] < rank[i2];
                };
                int ansi = -1, ansj = -1;
                for (int i = 0; i < n; i++) {
                    int lcnt = min(k - 1, i / l);
                    int rcnt = k - 1 - lcnt;
                    int j = n - 1 - rcnt * l;
                    if (!lcnt && i) continue;
                    if (!rcnt && j != n - 1) continue;
                    if (j - i + 1 < l) continue;
                    if (!~ansi || cmp(ansi, ansj, i, j)) {
                        ansi = i;
                        ansj = j;
                    }
                }
                cout << st.substr(ansi, ansj - ansi + 1) << "\n";
            }
        }
        else cout << "NO\n";
    }

    return 0;
}
