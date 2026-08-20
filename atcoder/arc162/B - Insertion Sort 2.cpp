#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> v(n);
    for (auto &e : v) cin >> e, --e;

    vector<pair<int, int>> ans;
    auto f = [&](int i, int j) {
        ans.emplace_back(i + 1, j);
        int a = v[i], b = v[i + 1];
        vector<int> nxt;
        if (nxt.size() == j) {
            nxt.push_back(a);
            nxt.push_back(b);
        }
        for (int k = 0; k < n; k++) if (k != i && k != i + 1) {
            nxt.push_back(v[k]);
            if (nxt.size() == j) {
                nxt.push_back(a);
                nxt.push_back(b);
            }
        }
        swap(v, nxt);
    };
    if ([&]() {
        for (int i = 0; i < n; i++) {
            int idx = find(v.begin(), v.end(), i) - v.begin();
            if (i == idx) continue;
            if (idx + 1 < n) f(idx, i);
            else {
                if (i + 1 < idx) {
                    f(idx - 2, idx - 1);
                    f(idx - 2, i);
                }
                else return false;
            }
        }
        return true;
    }()) {
        assert(ans.size() <= 2000);
        cout << "Yes\n";
        cout << ans.size() << "\n";
        for (auto [a, b] : ans) cout << a << " " << b << "\n";
    }
    else cout << "No\n";
    // }

    return 0;
}
