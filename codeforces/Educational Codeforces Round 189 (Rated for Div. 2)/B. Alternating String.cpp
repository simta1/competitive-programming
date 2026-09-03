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
        int cnt = 0;
        for (int i = 0, j = 0; i < n; i = j) {
            while (j < n && ~(st[i] + i + st[j] + j) & 1) ++j;
            ++cnt;
        }
        if (cnt <= 3) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
