#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, k;
        cin >> n >> k;

        vector<int> v(n);
        for (auto &e : v) cin >> e;

        sort(v.begin(), v.end());
        int ans = 0;
        vector<int> ls;
        for (int i = 0, j = 0; i < n; i = j) {
            while (j < n && v[i] == v[j]) ++j;
            ++ans;
            ls.push_back(j - i);
        }
        sort(ls.begin(), ls.end());
        for (auto cnt : ls) {
            if (k >= cnt) {
                k -= cnt;
                --ans;
            }
            else break;
        }

        cout << max(1, ans) << "\n";
    }

    return 0;
}
