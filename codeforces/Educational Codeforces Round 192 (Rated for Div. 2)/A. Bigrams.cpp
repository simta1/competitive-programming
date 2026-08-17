#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<int> v(n);
        for (auto &e : v) cin >> e;

        if ([&]() {
            int cnt = 0;
            for (auto e : v) {
                if (e >= 3) return true;
                cnt += e >= 2;
            }
            return cnt >= 2;
        }()) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
