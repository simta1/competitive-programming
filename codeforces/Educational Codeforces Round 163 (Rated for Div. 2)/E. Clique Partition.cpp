#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> f(int n) {
    vector<int> v;
    for (int i = n / 2; i >= 1; i--) v.push_back(i);
    for (int i = n; i > n / 2; i--) v.push_back(i);
    return v;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, k;
        cin >> n >> k;

        int cnt = (n + k - 1) / k;

        vector<int> a(n), c(n);
        int x = n % cnt;
        int y = cnt - x;

        iota(a.begin(), a.end(), 1);
        int cur = 1;
        for (int i = 0, j = 0; i < n; i = j) {
            j = min(i + k, n);
            int m = i + j >> 1;
            reverse(a.begin() + i, a.begin() + m);
            reverse(a.begin() + m, a.begin() + j);
            for (int idx = i; idx < j; idx++) c[idx] = cur;
            ++cur;
        }

        for (auto &e : a) cout << e << " ";
        cout << "\n";
        cout << cnt << "\n";
        for (auto &e : c) cout << e << " ";
        cout << "\n";
    }

    return 0;
}
