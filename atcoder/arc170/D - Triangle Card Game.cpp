#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<int> a(n), b(n);
        for (auto &e : a) cin >> e;
        for (auto &e : b) cin >> e;
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        vector<vector<pair<int, int>>> evt(n);
        multiset<int> s;
        constexpr int INF = 2e9;
        for (int i = 0, u = 0; i < n; i++) {
            while (u < n && a[u] <= b[i]) ++u;
            int mn = INF, mn2 = INF, mi = -1, mi2 = -1;
            for (int j = u - 2; j <= u + 1; j++) if (j >= 0 && j < n) {
                int dist = abs(b[i] - a[j]);
                int idx = j;
                if (mn > dist) {
                    swap(mn, dist);
                    swap(mi, idx);
                }
                if (mn2 > dist) {
                    swap(mn2, dist);
                    swap(mi2, idx);
                }
            }
            s.insert(mn);
            evt[mi].emplace_back(mn, mn2);
        }

        bool ans = false;
        int mnb = b[0];
        for (int i = 0; i < n; i++) {
            for (auto [cur, nxt] : evt[i]) {
                s.erase(s.find(cur));
                s.insert(nxt);
            }
            bool res = *s.rbegin() < a[i];
            if (mnb <= a[i]) {
                int cnt = lower_bound(a.begin(), a.end(), a[i] + mnb) - upper_bound(a.begin(), a.end(), a[i] - mnb);
                if (a[i] > a[i] - mnb && a[i] < a[i] + mnb) --cnt;
                res &= cnt > 0;
            }
            if (res) ans = true;
            for (auto [prv, cur] : evt[i]) {
                s.erase(s.find(cur));
                s.insert(prv);
            }
        }
        if (ans) cout << "Alice\n";
        else cout << "Bob\n";
    }

    return 0;
}
