#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, k, q;
    cin >> n >> k >> q;

    vector<array<int, 3>> evt;
    for (int i = 0; i < q; i++) {
        int p, l, r;
        cin >> p >> l >> r;
        evt.push_back({l, -1, i});
        evt.push_back({r, 1, i});
    }

    vector<int> ans(q);
    sort(evt.begin(), evt.end());
    int cnt = n;
    for (auto [t, add, idx] : evt) {
        cnt += add;
        if (add > 0 && cnt == 1) ans[idx] = 1;
    }

    cnt = 0;
    for (auto [t, add, idx] : evt) if (ans[idx]) {
        cnt -= add;
        if (cnt > k) {
            cout << "impossible";
            return 0;
        }
    }

    for (int i = 0; i < q; i++) cout << ans[i];

    return 0;
}
