#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        string st;
        cin >> st;

        auto ch = *min_element(st.begin(), st.end());
        int idx;
        for (int i = 0; i < n; i++) {
            if (st[i] == ch) idx = i;
        }

        cout << st[idx];
        for (int i = 0; i < n; i++) if (i != idx) {
            cout << st[i];
        }
        cout << "\n";
    }

    return 0;
}
