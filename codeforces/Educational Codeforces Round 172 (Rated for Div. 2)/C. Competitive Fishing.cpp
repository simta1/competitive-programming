#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, k;
        cin >> n >> k;

        string st;
        cin >> st;

        vector<int> sfs(n + 2);
        for (int i = 1; i <= n; i++) {
            if (st[i - 1] == '1') sfs[i] = 1;
            else sfs[i] = -1;
        }
        for (int i = n - 1; i > 0; i--) sfs[i] += sfs[i + 1];

        vector<int> v;
        for (int i = 2; i <= n; i++) if (sfs[i] > 0) v.push_back(sfs[i]);
        sort(v.rbegin(), v.rend());

        int sum = 0, cnt = 0;
        for (auto e : v) {
            sum += e;
            ++cnt;
            if (sum >= k) break;
        }

        if (sum < k) cout << "-1\n";
        else cout << cnt + 1 << "\n";
    }

    return 0;
}
