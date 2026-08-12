#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<int> v(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> v[i];
            v[i] += v[i - 1];
        }

        [&]() {
            for (int i = 1; i <= n; i++) {
                for (int j = i + 1; j < n; j++) {
                    int a = v[i] % 3;
                    int b = (v[j] - v[i]) % 3;
                    int c = (v[n] - v[j]) % 3;
                    if (a == b && b == c || a != b && b != c && c != a) {
                        cout << i << " " << j << "\n";
                        return;
                    }
                }
            }
            cout << "0 0\n";
        }();
    }

    return 0;
}
