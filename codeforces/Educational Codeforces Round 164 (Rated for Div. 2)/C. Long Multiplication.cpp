#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        string a, b;
        cin >> a >> b;

        int n = a.size();
        int idx = 0;
        while (idx < n && a[idx] == b[idx]) ++idx;
        if (idx < n) {
            if (a[idx] > b[idx]) swap(a[idx], b[idx]);
            for (int i = idx + 1; i < a.size(); i++) {
                if (a[i] < b[i]) swap(a[i], b[i]);
            }
        }
        cout << a << "\n" << b << "\n";
    }

    return 0;
}
