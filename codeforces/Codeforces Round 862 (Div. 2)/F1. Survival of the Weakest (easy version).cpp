#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll add = 0;
constexpr ll MOD = 1e9 + 7;

void f(vector<int> &v) {
    auto mn = *min_element(v.begin(), v.end());
    for (auto &e : v) e -= mn;
    add = (add + mn) * 2 % MOD;

    priority_queue<array<int, 3>> pq;
    int n = v.size();
    for (int i = 0; i + 1 < n; i++) pq.push({-v[i] - v[i + 1], i, i + 1});

    vector<int> res(n - 1);
    for (int it = 1; it < n; it++) {
        auto [sum, i, j] = pq.top();
        pq.pop();
        res[it - 1] = -sum;
        if (j + 1 < n) pq.push({-v[i] - v[j + 1], i, j + 1});
    }
    swap(res, v);
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> v(n);
    for (auto &e : v) cin >> e;
    sort(v.begin(), v.end());

    for (int i = 1; i < n; i++) f(v);
    int ans = add + v[0];
    if (ans >= MOD) ans -= MOD;
    cout << ans;

    return 0;
}
