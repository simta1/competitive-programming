#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, k;

string qry(int x, int y) {
    cout << x + 1 << " " << y + 1 << endl;
    string st;
    cin >> st;
    if (st == "sunk") {
        if (--k == 0) exit(0);
    }
    return st;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    cin >> n >> k;

    auto f = [&](int ci, int cj) {
        for (int i = ci - 1; i >= max(0, ci - 4); i--) qry(i, cj);
        for (int i = ci + 1; i <= min(n - 1, ci + 4); i++) qry(i, cj);
        for (int j = cj - 1; j >= max(0, cj - 4); j--) qry(ci, j);
        for (int j = cj + 1; j <= min(n - 1, cj + 4); j++) qry(ci, j);
    };

    vector<pair<int, int>> v;
    for (int i = 0; i < n; i++) {
        for (int j = i % 5; j < n; j += 5) {
            if (qry(i, j) == "hit") v.emplace_back(i, j);
        }
    }
    for (auto [i, j] : v) f(i, j);
    

    return 0;
}
