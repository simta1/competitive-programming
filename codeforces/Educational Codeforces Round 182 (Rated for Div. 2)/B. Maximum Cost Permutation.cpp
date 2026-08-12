#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<int> v(n + 1);
        vector<bool> used(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> v[i];
            used[v[i]] = 1;
        }

        vector<int> a;
        for (int i = 1; i <= n; i++) {
            if (!used[i]) a.push_back(i);
        }

        for (int i = 1; i <= n; i++) {
            if (!v[i]) {
                v[i] = a.back();
                a.pop_back();
            }
        }

        int mn = n + 1, mx = 0;
        for (int i = 1; i <= n; i++) {
            if (v[i] != i) {
                mn = min(mn, i);
                mx = max(mx, i);
            }
        }
        cout << max(0, mx - mn + 1) << "\n";
        

        
    }

    return 0;
}
