#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> a(n), b(n);
    for (auto &e : a) cin >> e;
    for (auto &e : b) cin >> e;

    vector<int> da(n), db(n);
    for (int i = 0, j = n - 1; i < n; j = i++) da[i] = a[i] ^ a[j];
    for (int i = 0, j = n - 1; i < n; j = i++) db[i] = b[i] ^ b[j];

    da.resize(2 * n);
    for (int i = 0; i < n; i++) da[i + n] = da[i];

    vector<int> pi(n);
    for (int i = 1, j = 0; i < n; i++) {
        while (j && db[i] != db[j]) j = pi[j - 1];
        if (db[i] == db[j]) pi[i] = ++j;
    }

    for (int i = 0, j = 0; i < 2 * n - 1; i++) {
        while (j && da[i] != db[j]) j = pi[j - 1];
        if (da[i] == db[j]) {
            if (j == n - 1) {
                int k = i - n + 1;
                int x = a[k] ^ b[0];
                cout <<  k << " " << x << "\n";
                j = pi[j];
            }
            else ++j;
        }
    }

    return 0;
}
