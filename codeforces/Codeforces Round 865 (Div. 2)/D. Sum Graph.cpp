#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void query1(int x) {
    cout << "+ " << x << endl;
    int res;
    cin >> res;
    assert(res == 1);
}

int query(int i, int j) {
    cout << "? " << i << " " << j << endl;
    int res;
    cin >> res;
    return res;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<int> v = {n};
        if (n & 1) {
            query1(n + 1);
            query1(n);
            while (v.size() < n) {
                v.push_back(n + 1 - v.back());
                v.push_back(n - v.back());
            }
        }
        else {
            query1(n + 1);
            query1(n);
            v.push_back(1);
            while (v.size() < n) {
                v.push_back(n - v.back());
                v.push_back(n + 1 - v.back());
            }
        }
        // for (auto &e : v) cout << e << " "; cout << "\n";

        int b = 1, mx = 0;
        for (int i = 2; i <= n; i++) {
            int d = query(1, i);
            if (mx < d) {
                mx = d;
                b = i;
            }
        }

        vector<int> ans(n + 1);
        ans[b] = 0;
        for (int i = 1; i <= n; i++) if (i != b) {
            int d = query(b, i);
            ans[i] = d;
        }
        cout << "! ";
        for (int i = 1; i <= n; i++) cout << v[ans[i]] << " ";
        for (int i = 1; i <= n; i++) cout << v[n - 1 - ans[i]] << " ";
        cout << endl;
        int res;
        cin >> res;
        assert(res == 1);
    }

    return 0;
}
