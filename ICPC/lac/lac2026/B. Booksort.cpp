#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> v(n);
    for (auto &e : v) cin >> e;

    set<pair<int, int>> s;
    for (int i = 0; i < n; i++) s.emplace(v[i], i);

    vector<pair<int, int>> ans;
    auto f = [&](int i, int j) {
        ans.emplace_back(i + 1, j + 1);
        int sum = v[i] + v[j];
        v[i] = sum >> 1;
        v[j] = sum + 1 >> 1;
        s.emplace(v[i], i);
        s.emplace(v[j], j);
    };

    while (1) {
        auto it = s.begin(), jt = prev(s.end());
        if (jt->first - it->first <= 1) break;
        int i = it->second, j = jt->second;
        s.erase(it);
        s.erase(jt);
        f(i, j);
    }

    int mn = s.begin()->first, mx = prev(s.end())->first;
    if (mn != mx) {
        int i = 0, j = n - 1;
        while (i < j) {
            while (i < n && v[i] == mn) ++i;
            while (j >= 0 && v[j] == mx) --j;
            if (i < j) f(i, j);
        }
    }

    assert(is_sorted(v.begin(), v.end()));

    cout << ans.size() << "\n";
    for (auto [i, j] : ans) cout << i << " " << j << "\n";

    return 0;
}
