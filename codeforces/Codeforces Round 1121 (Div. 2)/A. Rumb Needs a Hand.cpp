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
        for (auto &e : v) cin >> e, --e;

        vector<int> a;
        for (int i = 0; i < n; i++) {
            if (v[i] != i) a.push_back(i);
        }

        for (int i = 0; i < a.size() / 2; i++) {
            swap(v[a[i]], v[a[a.size() - 1 - i]]);
        }

        if (is_sorted(v.begin(), v.end())) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
