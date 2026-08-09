#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        string st;
        cin >> st;

        int n = st.size();
        bool same = true;
        for (int i = 1; i < n; i++) {
            if (st[i] != st[0]) same = false;
        }
        if (same) cout << "-1\n";
        else cout << n - 1 << "\n";
    }

    return 0;
}
