#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    string a, b;
    cin >> a >> b;

    int cnt[26]{};
    for (auto ch : a) ++cnt[ch - 'a'];
    for (auto ch : b) --cnt[ch - 'a'];

    for (int i = 0; i < 26; i++) {
        if (cnt[i]) {
            cout << -1;
            return 0;
        }
    }

    vector<int> last(26, n);
    vector nxt(n, vector<int>(26));
    for (int i = n - 1; i >= 0; i--) {
        nxt[i] = last;
        last[b[i] - 'a'] = i;
    }

    auto check = [&](int len) {
        int cur = -1;
        for (int i = len; i < n; i++) {
            int pos = last[a[i] - 'a'];
            if (~cur) pos = nxt[cur][a[i] - 'a'];
            if (pos == n) return false;
            cur = pos;
        }
        return true;
    };

    int lo = -1, hi = n;
    while (lo + 1 < hi) {
        int mid = lo + hi >> 1;
        if (check(mid)) hi = mid;
        else lo = mid;
    }
    cout << hi;

    return 0;
}
