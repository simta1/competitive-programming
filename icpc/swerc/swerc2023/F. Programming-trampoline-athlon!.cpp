#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<tuple<int, int, string>> v(n);
    for (int i = 0; i < n; i++) {
        string st;
        int x, a, b, c, d, e, f;
        cin >> st >> x >> a >> b >> c >> d >> e >> f;

        int mn = min({a, b, c, d, e, f});
        int mx = max({a, b, c, d, e, f});
        int score = 10 * x + a + b + c + d + e + f - mn - mx;
        v[i] = {-score, i, st};
    }

    sort(v.begin(), v.end());
    int cnt = 0;
    for (int i = 0, j = 0; i < n; i = j) {
        while (j < n && get<0>(v[i]) == get<0>(v[j])) ++j;
        for (int k = i; k < j; k++) {
            auto [score, _, name] = v[k];
            cout << name << " " << -score << "\n";
        }
        cnt += j - i;
        if (cnt > 2) break;
    }
    return 0;
}
