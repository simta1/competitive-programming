#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<pair<int, int>> a, b;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i + j & 1) a.emplace_back(i, j);
            else b.emplace_back(i, j);
        }
    }

    for (int _ = n * n; _--;) {
        int x;
        cin >> x;
        if (x != 1) {
            if (!a.empty()) {
                auto [i, j] = a.back();
                a.pop_back();
                cout << "1 " << i << " " << j << endl;
            }
            else {
                auto [i, j] = b.back();
                b.pop_back();
                cout << (2 ^ 3 ^ x) << " " << i << " " << j << endl;
            }
        }
        else {
            if (!b.empty()) {
                auto [i, j] = b.back();
                b.pop_back();
                cout << "2 " << i << " " << j << endl;
            }
            else {
                auto [i, j] = a.back();
                a.pop_back();
                cout << (1 ^ 3 ^ x) << " " << i << " " << j << endl;
            }
        }
    }

    return 0;
}
