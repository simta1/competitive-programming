#include <bits/stdc++.h>
using namespace std;
using ll = long long;

string f(int n) {
    int q = (n - 2) / 3;
    int r = (n - 2) % 3;
    if (r == 0) return string(q, '0') + "1" + string(q, '0') + "1" + string(q, '0');
    if (r == 1) return string(q, '0') + "1" + string(q + 1, '0') + "1" + string(q, '0');
    return string(q + 1, '0') + "1" + string(q, '0') + "1" + string(q + 1, '0');
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    // constexpr int N = 18;
    // int mn = 1e9;
    // for (int mask = 0; mask < (1 << N); mask++) if (__builtin_popcount(mask) <= 3) {
    //     string st = bitset<N>(mask).to_string();
    //     int cnt = 0;
    //     for (int i = 0; i < N; i++) {
    //         for (int j = i; j < N; j++) {
    //             if (stoi(st.substr(i, j - i + 1), 0, 2) % 3 == 0) ++cnt;
    //         }
    //     }
    //     mn = min(mn, cnt);
    // }
    // // for (int mask = 0; mask < (1 << N); mask++) if (__builtin_popcount(mask) <= 3) {
    // for (int mask = 0; mask < (1 << N); mask++) if (__builtin_popcount(mask) == 2) {
    //     string st = bitset<N>(mask).to_string();
    //     int cnt = 0;
    //     for (int i = 0; i < N; i++) {
    //         for (int j = i; j < N; j++) {
    //             if (stoi(st.substr(i, j - i + 1), 0, 2) % 3 == 0) ++cnt;
    //         }
    //     }
    //     if (mn == cnt) cout << st << "\n";
    // }

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        if (n & 1) {
            if (n == 1) cout << "1\n";
            else cout << f(n) << "\n";
        }
        else {
            if (n == 2) cout << "11\n";
            else {
                cout << f(n - 1) << "01"[(n - 4) / 2 % 3 == 2] << "\n";
            }
        }
    }

    return 0;
}
