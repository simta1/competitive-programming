#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, x;
    cin >> n >> x;

    vector<int> cnt(x + 1);
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        ++cnt[a];
    }

    for (int i = 1; i < x; i++) if (cnt[i]) {
        if (cnt[i] % (i + 1)) {
            cout << "No";
            return 0;
        }

        cnt[i + 1] += cnt[i] / (i + 1);
    }

    cout << "Yes";
    return 0;
}
