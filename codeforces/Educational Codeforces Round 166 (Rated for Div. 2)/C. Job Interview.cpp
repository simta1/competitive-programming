#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> a, b;
map<array<int, 3>, ll> x, y;
constexpr ll INF = 1e18;
ll f(int i, int n, int m) {
    if (i == a.size()) return 0;
    if (x.count({i, n, m})) return x[{i, n, m}];
    auto &res = x[{i, n, m}];
    res = -INF;
    if (a[i] > b[i]) {
        assert(i < a.size());
        if (n) res = max(res, f(i + 1, n - 1, m) + a[i]);
        else if (m) res = max(res, f(i + 1, n, m - 1) + b[i]);
    }
    else {
        if (m) res = max(res, f(i + 1, n, m - 1) + b[i]);
        else if (n) res = max(res, f(i + 1, n - 1, m) + a[i]);
    }
    return res;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, m;
        cin >> n >> m;

        a = vector<int>(n + m + 1);
        b = vector<int>(n + m + 1);
        x.clear(), y.clear();
        for (auto &e : a) cin >> e;
        for (auto &e : b) cin >> e;

        ll cur = 0;
        int tmp = n + m + 1;
        for (int i = 0; i < tmp; i++) {
            cout << cur + f(i + 1, n, m) << " ";
            if (a[i] > b[i]) {
                if (n) {
                    cur += a[i];
                    --n;
                }
                else {
                    cur += b[i];
                    --m;
                }
            }
            else {
                if (m) {
                    cur += b[i];
                    --m;
                }
                else {
                    cur += a[i];
                    --n;
                }
            }
        }

        cout << "\n";
    }

    return 0;
}
