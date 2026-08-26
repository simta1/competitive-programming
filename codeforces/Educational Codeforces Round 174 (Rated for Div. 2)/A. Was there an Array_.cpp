#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<int> v(n - 2);
        for (auto &e : v) cin >> e;

        if ([&]() {
            for (int i = 1; i + 1 < v.size(); i++) {
                if (v[i - 1] && !v[i] && v[i + 1]) return false;
            }
            return true;
        }()) cout << "YES\n";
        else cout << "NO\n";

    }

    return 0;
}
