#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    using ld = long double;
    vector<ld> v(n);
    for (auto &e : v) cin >> e;

    int mxIdx = max_element(v.begin(), v.end()) - v.begin();

    for (int val = 1; val <= 10000; val++) {
        vector<int> ans(n);

        if ([&]() {
            for (int i = 0; i < n; i++) {
                ld tmp = v[i] / v[mxIdx] * val;
                ll x = llround(tmp);
                if (abs(tmp - x) > 1e-5) return false;
                ans[i] = llround(v[i] / v[mxIdx] * val);
            }

            int g = 0;
            for (auto &e : ans) g = __gcd(g, e);
            for (auto &e : ans) e /= g;

            ld sum = 0;
            for (int i = 0; i < n; i++) sum += ll(ans[i]) * ans[i];
            sum = sqrt(sum);
            for (int i = 0; i < n; i++) {
                if (abs(ans[i] / sum - v[i]) > 1e-6) return false;
            }
            return true;
        }()) {
            for (auto &e : ans) cout << e << "\n";
            return 0;
        }
    }
    return 0;
}
