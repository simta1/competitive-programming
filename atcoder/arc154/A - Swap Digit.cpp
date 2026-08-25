#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    string a, b;
    cin >> a >> b;

    for (int i = 0; i < n; i++) {
        if (a[i] > b[i]) swap(a[i], b[i]);
    }

    constexpr ll MOD = 998'244'353;
    ll x = 0, y = 0;
    for (int i = 0; i < n; i++) {
        x = x * 10 + a[i] - '0';
        y = y * 10 + b[i] - '0';
        x %= MOD;
        y %= MOD;
    }
    // cout << x << " " << y << "::\n";

    cout << x * y % MOD;

    return 0;
}
