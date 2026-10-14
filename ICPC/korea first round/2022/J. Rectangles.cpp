#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<pair<int, int>> v(n);
    vector<int> xs, ys;
    for (auto &[x, y] : v) {
        cin >> x >> y;
        xs.push_back(x);
        ys.push_back(y);
    }

    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    vector<vector<int>> cols(xs.size());
    for (auto &[x, y] : v) {
        x = lower_bound(xs.begin(), xs.end(), x) - xs.begin();
        y = lower_bound(ys.begin(), ys.end(), y) - ys.begin();
        cols[x].push_back(y);
    }

    int sqr = sqrt(n);
    ll ans = 0;
    vector<int> active(ys.size(), -1), cnt(xs.size());
    for (int x = 0; x < xs.size(); x++) if (cols[x].size() >= sqr) {
        for (auto y : cols[x]) active[y] = x;

        for (auto [cx, cy] : v) {
            if (cx != x && active[cy] == x) {
                if (cols[cx].size() < sqr || cx < x) {
                    ++cnt[cx];
                }
            }
        }

        for (int i = 0; i < xs.size(); i++) {
            ans += cnt[i] * ll(cnt[i] - 1) / 2;
            cnt[i] = 0;
        }
    }

    vector<pair<int, int>> a;
    for (int x = 0; x < xs.size(); x++) if (cols[x].size() < sqr) {
        const auto &col = cols[x];
        for (int i = 0; i < col.size(); i++) {
            for (int j = i + 1; j < col.size(); j++) {
                a.push_back(minmax(col[i], col[j]));
            }
        }
    }

    sort(a.begin(), a.end());
    for (int i = 0, j = 0; i < a.size(); i = j) {
        while (j < a.size() && a[i] == a[j]) ++j;
        int cnt = j - i;
        ans += cnt * ll(cnt - 1) / 2;
    }
    cout << ans;
    return 0;
}
