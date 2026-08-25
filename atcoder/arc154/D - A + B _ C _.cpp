#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool query(int i, int j, int k) {
    cout << "? " << i << " " << j << " " << k << endl;
    string st;
    cin >> st;
    return st[0] == 'Y';
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    int one = 1;
    for (int i = 2; i <= n; i++) {
        if (!query(i, i, one)) one = i;
    }

    auto cmp = [&](int i, int j) { // p[i] < p[j]
        return query(j, one, i);
    };

    vector<int> v(n);
    iota(v.begin(), v.end(), 1);
    auto f = [&](auto &&f, int s, int e) {
        if (s == e) return;

        int m = s + e >> 1;
        f(f, s, m);
        f(f, m + 1, e);
        vector<int> res(e - s + 1);
        merge(v.begin() + s, v.begin() + m + 1,
              v.begin() + m + 1, v.begin() + e + 1, res.begin(),
              cmp);
        for (int i = s; i <= e; i++) v[i] = res[i - s];
    };
    f(f, 0, n - 1);

    vector<int> ans(n + 1);
    int cur = 0;
    for (auto i : v) ans[i] = ++cur;

    cout << "! ";
    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << endl;

    return 0;
}
