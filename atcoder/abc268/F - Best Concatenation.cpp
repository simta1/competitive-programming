#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<tuple<string, ll, ll>> v(n);
    for (auto &[st, k, d] : v) {
        cin >> st;
        for (auto ch : st) {
            if (ch == 'X') ++k;
            else d += ch - '0';
        }
    }

    using elem = tuple<string, ll, ll>;
    sort(v.begin(), v.end(), [&](const elem &a, const elem &b) {
        return get<1>(a) * get<2>(b) > get<2>(a) * get<1>(b);
    });

    int k = 0;
    ll ans = 0;
    for (auto &[st, _, __] : v) {
        for (auto ch : st) {
            if (ch == 'X') ++k;
            else ans += ll(ch - '0') * k;
        }
    }
    cout << ans;

    return 0;
}
