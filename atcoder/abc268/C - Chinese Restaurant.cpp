#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> v(n);
    for (auto &e : v) cin >> e;

    auto f = [&](int x) {
        x %= n;
        if (x < 0) x += n;
        return x;
    };

    vector<int> cnt(n);
    for (int i = 0; i < n; i++) {
        int x = f(v[i] - i);
        ++cnt[x];
        ++cnt[f(x + 1)];
        ++cnt[f(x - 1)];
    }

    cout << *max_element(cnt.begin(), cnt.end());

    return 0;
}
