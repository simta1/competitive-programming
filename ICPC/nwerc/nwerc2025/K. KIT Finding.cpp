#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, m, k, i, t;
    cin >> n >> m >> k >> i >> t;

    vector v(n, vector<int>(m));
    for (auto &r : v) for (auto &e : r) cin >> e;

    string st = "KIT" + string(t - 1, 'T') + string (k - 1, 'K') + string(i - 1, 'I');

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cout << st[i * m + j];
        cout << "\n";
    }

    return 0;
}
