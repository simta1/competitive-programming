#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> v(n + 2, -1);
    v[0] = v[n + 1] = 1e8;

    // v[1] = 3, v[2] = 2, v[3] = 1, v[4] = 4, v[5] = 5;

    auto qry = [&](int i) {
        if (~v[i]) return v[i];
        cout << "? " << i << endl;
        cin >> v[i];
        return v[i];
    };

    int lo = 0, hi = n + 1;
    while (lo + 2 < hi) {
        int i = lo + hi >> 1;
        int j = i + 1;
        assert(lo < i && i < j && j < hi);
        if (qry(i) < qry(j)) hi = j;
        else lo = i;
    }

    cout << "! " << lo + 1 << endl;

    return 0;
}
