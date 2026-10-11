#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int top2(priority_queue<int> &pq) {
    int x = pq.top();
    pq.pop();
    int res = pq.top();
    pq.push(x);
    return res;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int l, k;
    cin >> l >> k;

    vector<int> c(k);
    for (auto &e : c) cin >> e;

    int n;
    cin >> n;

    vector<array<int, 3>> v(n);
    for (auto &[y, x, idx] : v) cin >> x >> y >> idx, --idx;

    sort(v.begin(), v.end());

    v.push_back({l + 1, l + 1, -1});

    vector<pair<int, int>> a(k);
    multiset<int> s, e;
    for (int i = 0; i < k; i++) {
        a[i] = c[i] ? pair{1, 0} : pair{0, l};
        s.insert(a[i].first);
        e.insert(a[i].second);
    }
    auto upd = [&](int idx, int x1, int x2) {
        s.erase(s.find(a[idx].first));
        e.erase(e.find(a[idx].second));
        a[idx] = {x1, x2};
        s.insert(a[idx].first);
        e.insert(a[idx].second);
    };

    vector<priority_queue<int>> pqs(k);

    ll ans = 0;
    int py = -1;
    for (auto [y, x, idx] : v) {
        int cnt = max(0, *e.begin() - *s.rbegin() + 1);
        ans += ll(y - py - 1) * cnt;

        if (~idx) {
            auto &pq = pqs[idx];
            pq.push(x);
            if (pq.size() > c[idx] + 1) pq.pop();
            if (pq.size() >= c[idx]) {
                if (pq.size() == c[idx]) {
                    upd(idx, !pq.empty() ? pq.top() + 1 : 0, l);
                }
                else {
                    upd(idx, pq.size() > 1 ? top2(pq) + 1 : 0, pq.top() - 1);
                }
            }
            ans += max(0, min(x - 1, *e.begin()) - *s.rbegin() + 1);
        }

        py = y;
    }
    cout << ans;

    return 0;
}
