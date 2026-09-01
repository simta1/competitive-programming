#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> v(n);
    for (auto &e : v) cin >> e;

    constexpr int N = 100'000;
    static int cnt[N + 1];

    ++cnt[v[0]];
    for (int i = 1; i < n; i++) if (v[i - 1] < v[i]) {
        --cnt[v[i - 1]];
        ++cnt[v[i]];
    }

    for (int i = 1; i <= N; i++) cnt[i] += cnt[i - 1];

    int mx = *max_element(v.begin(), v.end());
    for (int k = 1; k <= mx; k++) {
        ll ans = 0;
        for (int x = 1; x <= (mx + k - 1) / k; x++) {
            ans += ll(cnt[min(mx, k * x)] - cnt[k * (x - 1)]) * x;
        }
        cout << ans << " ";
    }

    // ceil(i/k) * cnt[i]
    // 1, 2, ..., i
    // ceil(i/k) = x
    // k(x - 1) < i <= kx

    return 0;
}
