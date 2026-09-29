#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T, const T& (*op)(const T&, const T&)>
struct RMQ {
    vector<vector<T>> ac; // ac[i][j] = op(v[j:j+2^i))
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

int mxodd(int n) {
    if (n & 1) return n;
    return n - 1;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> v(n);
    for (auto &e : v) cin >> e;

    vector<int> right_desc(n), left_desc(n), right_inc(n), left_inc(n);
    left_inc[0] = left_desc[0] = 0;
    for (int i = 1; i < n; i++) {
        if (v[i - 1] < v[i]) {
            left_desc[i] = 1 + left_desc[i - 1];
            left_inc[i] = 0;
        }
        else {
            left_desc[i] = 0;
            left_inc[i] = 1 + left_inc[i - 1];
        }
    }
    right_inc[n - 1] = right_desc[n - 1] = 0;
    for (int i = n - 2; i >= 0; i--) {
        if (v[i] < v[i + 1]) {
            right_inc[i] = 1 + right_inc[i + 1];
            right_desc[i] = 0;
        }
        else {
            right_inc[i] = 0;
            right_desc[i] = 1 + right_desc[i + 1];
        }
    }

    vector<int> ymx(n);
    for (int i = 0; i < n; i++) {
        ymx[i] = max(left_inc[i], right_inc[i]);
    }
    const RMQ<int, max> rmq(ymx);

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int a = left_desc[i], b = right_desc[i];
        if (a < 2 || b < 2) continue;

        ans += [&]() -> bool {
            // if (i == 2) cout << a << " " << b << "\n";
            if (b && a <= mxodd(b)) return false;
            if (a && b <= mxodd(a)) return false;
            // if (i == 2) cout << "::\n";

            if (max(a, b) <= right_inc[i + b]) return false;
            if (max(a, b) <= left_inc[i - a]) return false;

            int mx = 0;
            if (i - a) mx = max(mx, rmq.query(0, i - a - 1));
            if (i + b + 1 < n) mx = max(mx, rmq.query(i + b + 1, n - 1));
            return mx < max(a, b);
        }();
    }
    cout << ans;

    return 0;
}
