#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<pair<int, int>> v(2 * n);
    for (auto &[x, y] : v) cin >> x >> y;

    sort(v.begin(), v.end());

    for (int i = 0, j = 0; i < v.size(); i = j) {
        while (j < v.size() && v[i] == v[j]) ++j;
        if (j - i & 1) {
            cout << "yes";
            return 0;
        }
    }
    
    cout << "no";
    return 0;
}
