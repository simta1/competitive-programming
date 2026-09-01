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

        auto check = [&](int k) {
            vector<bool> v(n - k);
            for (int i = 0; i < n - k; i++) {
                if (st[i] == st[i + k] || st[i] == '?' || st[i + k] == '?') v[i] = 1;
            }

            for (int i = 0, j = 0; i < v.size(); i = j) {
                while (j < v.size() && v[i] == v[j]) ++j;
                if (v[i] && j - i >= k) return true;
            }
            return false;
        };

        bool flag = false;
        for (int i = n / 2; i >= 1; i--) if (check(i)) {
            cout << 2 * i << "\n";
            flag = 1;
            break;
        }
        if (!flag) cout << "0\n";
    }

    return 0;
}
