#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, m;
        cin >> n >> m;

        vector<int> v(n);
        for (auto &e : v) cin >> e;

        ll sum = 0, ans = -9e18;
        priority_queue<int> pq;
        for (int i = 0; i < n; i++) {
            if (pq.size() == m - 1) {
                ans = max(ans, -sum + m * ll(v[i]));
            }

            sum += v[i];
            pq.push(v[i]);
            if (pq.size() == m) {
                sum -= pq.top();
                pq.pop();
            }
        }
        cout << ans << "\n";
    }

    return 0;
}
