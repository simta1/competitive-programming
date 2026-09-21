#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<int> cnt(n);
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            ++cnt[x];
        }

        cout << [&]() {
            bool flag = 0;
            for (int i = 0; i < n; i++) {
                if (!cnt[i]) return i;
                else if (cnt[i] == 1) {
                    if (!flag) flag = 1;
                    else return i;
                }
            }
            return n;
        }() << "\n";
    }

    return 0;
}
