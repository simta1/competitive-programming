#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> v(n);
    for (auto &e : v) cin >> e;

    sort(v.begin(), v.end());
    vector<int> odd;
    for (int i = 0, j = 0; i < n; i = j) {
        while (j < n && v[i] == v[j]) ++j;
        if (j - i & 1) odd.push_back(v[i]);
    }
    
    if (odd.empty()) {
        cout << 0;
        return 0;
    }

    int x = 0;
    for (auto e : odd) x ^= e;
    if (x) {
        cout << -1;
        return 0;
    }

    cout << odd.back() - 1;

    return 0;
}
