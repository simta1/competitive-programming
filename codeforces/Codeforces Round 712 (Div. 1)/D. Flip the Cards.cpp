#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> v(n), dir(n);
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        if (a > b) {
            swap(a, b);
            dir[a] = 1;
        }

        if (a < n && b >= n) {
            v[a] = b - n;
        }
        else {
            cout << -1;
            return 0;
        }
    }

    auto pref_mn = v, suf_mx = v;
    for (int i = 1; i < n; i++) pref_mn[i] = min(pref_mn[i], pref_mn[i - 1]);
    for (int i = n - 2; i >= 0; i--) suf_mx[i] = max(suf_mx[i], suf_mx[i + 1]);

    int pi = 0;
    vector<pair<int, int>> a;
    for (int i = 0; i + 1 < n; i++) {
        if (pref_mn[i] > suf_mx[i + 1]) {
            a.emplace_back(pi, i);
            pi = i + 1;
        }
    }
    if (pi < n) a.emplace_back(pi, n - 1);

    int ans = 0;
    for (auto [s, e] : a) {
        int t1 = n, t2 = n;
        int cnt = 0;
        for (int i = s; i <= e; i++) {
            if (t1 > v[i] && t2 > v[i]) {
                if (t1 > t2) {
                    t2 = v[i];
                    cnt += !dir[i];
                }
                else {
                    t1 = v[i];
                    cnt += dir[i];
                }
            }
            else if (t1 > v[i]) {
                t1 = v[i];
                cnt += dir[i];
            }
            else if (t2 > v[i]) {
                t2 = v[i];
                cnt += !dir[i];
            }
            else {
                cout << -1;
                return 0;
            }
        }
        ans += min(cnt, e - s + 1 - cnt);
    }
    cout << ans;

    return 0;
}
