#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> v(n);
    for (auto &e : v) cin >> e;

    // v[l] = (l+r+1) : (l,r) -> (l+1, r)
    // v[n-1-r] = (l+r+1) : (l,r) -> (l, r+1)
    vector<vector<int>> down(n), right(n);
    for (int i = 0; i < n; i++) {
        int l = i, r = v[i] - l - 1;
        if (r >= 0) down[l].push_back(r);

        r = n - 1 - i, l = v[i] - r - 1;
        if (l >= 0) right[l].push_back(r);
    }
    for (int i = 0; i < n; i++) {
        sort(down[i].begin(), down[i].end());
        sort(right[i].begin(), right[i].end());
    }

    map<int, int> mp;
    mp[0] = 0;

    auto add = [&](int idx) {
        auto it = mp.upper_bound(idx);
        int val = prev(it)->second + 1;
        if (prev(it)->first == idx) prev(it)->second = val;
        else mp.emplace(idx, val);

        if (it != mp.end() && it->second == val) mp.erase(it);
    };

    int mx = 0;
    for (int i = 0; i < n; i++) {
        for (auto j : right[i]) if (!mp.count(j + 1) || prev(mp.lower_bound(j + 1))->second + 1 > mp[j + 1]) add(j + 1);
        mx = max(mx, prev(mp.upper_bound(n - i))->second);
        for (auto j : down[i]) add(j);
    }

    cout << n - mx;

    return 0;
}
