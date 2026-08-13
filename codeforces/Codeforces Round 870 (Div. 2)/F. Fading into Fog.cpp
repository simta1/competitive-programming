#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = double;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        auto qry = [&](ld a, ld b, ld c) {
            cout << "? " << a << " " << b << " " << c << endl;
            vector<pair<ld, ld>> res(n);
            for (auto &[x, y] : res) cin >> x >> y;
            return res;
        };

        vector<ld> xs, ys;
        for (auto [x, y] : qry(0, 1, 0)) xs.push_back(x);
        for (auto [x, y] : qry(1, 0, 0)) ys.push_back(y);
        vector<ld> v;
        for (auto [x, y] : qry(1, 0.001, 0)) v.push_back(y);

        sort(ys.begin(), ys.end());
        sort(v.begin(), v.end());

        cout << "! ";
        for (int i = 0; i < n; i++) {
            ld y = ys[i];
            // v[i] = (y - 0.001x) / (1+1e-6)
            for (auto x : xs) {
                ld tmp = (y - 0.001 * x) / 1.000001;
                if (abs(tmp - v[i]) <= 0.0005) {
                    cout << x << " " << y << " ";
                    break;
                }
            }
        }
        cout << endl;
    }

    return 0;
}
