#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> v(n);
    for (auto &e : v) cin >> e;

    sort(v.begin(), v.end());

    int cnt = 0;
    for (int i = 0, j = 0; i < n; i = j) {
        while (j < n && v[i] == v[j]) ++j;
        if (j - i & 1) ++cnt;
    }

    if (cnt <= 1) cout << "E";
    else cout << "FS"[cnt & 1];

    return 0;
}
