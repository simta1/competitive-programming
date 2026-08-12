#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int f(int a, int b, int c) {
    int x = a + b - c;
    int y = b + c - a;
    int z = c + a - b;
    if (x > 0 && y > 0 && z > 0) return x * y * z * (x + y + z);
    return 0;
}

int query(int i, int j, int k) {
    cout << "? " << i << " " << j << " " << k << endl;
    int res;
    cin >> res;
    return res;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    // for (int a = 1; a <= 4; a++) {
    //     for (int b = a; b <= 4; b++) {
    //         for (int c = b; c <= 4; c++) {
    //             cout << a << " " << b << " " << c << " " << f(a, b, c) << "\n";
    //         }
    //     }
    // }
    // cout << "--\n";

    
    int dp[5][5]{};
    for (int a = 1; a <= 4; a++) {
        for (int c = 1; c <= 4; c++) {
            dp[a][c] = f(a, a, c);
            // cout << a << " " << a << " " << c << " " << f(a, a, c) << "\n";
        }
    }

    int n;
    cin >> n;

    if (n < 9) {
        // 8C3=56
        // 8C3 * 4^8 = 917504
        vector<int> qs(56);
        int idx = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                for (int k = j + 1; k <= n; k++) {
                    qs[idx++] = query(i, j, k);
                }
            }
        }

        vector<vector<int>> candi;
        for (int mask = 0; mask < (1 << 2 * n); mask++) {
            vector<int> v(n + 1);
            for (int i = 0; i < n; i++) v[i + 1] = (mask >> 2 * i & 3) + 1;
            if ([&]() {
                int idx = 0;
                for (int i = 1; i <= n; i++) {
                    for (int j = i + 1; j <= n; j++) {
                        for (int k = j + 1; k <= n; k++) {
                            if (qs[idx++] != f(v[i], v[j], v[k])) return false;
                        }
                    }
                }
                return true;
            }()) candi.push_back(v);
        }
        if (candi.size() != 1) cout << "! -1" << endl;
        else {
            cout << "! ";
            for (int i = 1; i <= n; i++) cout << candi[0][i] << " ";
            cout << endl;
        }
    }
    else {
        vector<int> ans(n + 1);
        int a = -1, b = -1, c = -1;
        for (int i = 1; i <= 9; i++) {
            for (int j = i + 1; j <= 9; j++) {
                for (int k = j + 1; k <= 9; k++) {
                    int x = query(i, j, k);
                    if (x == 3) {
                        ans[i] = ans[j] = ans[k] = 1;
                        a = i, b = j, c = k;
                    }
                    else if (x == 48) {
                        ans[i] = ans[j] = ans[k] = 2;
                        a = i, b = j, c = k;
                    }
                    else if (x == 243) {
                        ans[i] = ans[j] = ans[k] = 3;
                        a = i, b = j, c = k;
                    }
                    else if (x == 768) {
                        ans[i] = ans[j] = ans[k] = 4;
                        a = i, b = j, c = k;
                    }
                }
            }
        }
        assert(~a);
        if (ans[a] == 1) {
            vector<int> big;
            for (int i = 1; i <= n; i++) if (i != a && i != b && i != c) {
                int x = query(a, b, i);
                if (x == 0) {
                    big.push_back(i);
                    if (big.size() >= 4) break;
                }
                else ans[i] = 1;
            }

            if (big.empty()) {
                cout << "! ";
                for (int i = 0; i < n; i++) cout << "1 ";
                cout << endl;
                return 0;
            }

            int i1 = -1, i2 = -1;
            for (int i = 0; i < big.size(); i++) {
                for (int j = i + 1; j < big.size(); j++) {
                    int x = query(a, big[i], big[j]);
                    if (x == 15) {
                        i1 = big[i], i2 = big[j];
                        ans[i1] = ans[i2] = 2;
                    }
                    else if (x == 35) {
                        i1 = big[i], i2 = big[j];
                        ans[i1] = ans[i2] = 3;
                    }
                    else if (x == 63) {
                        i1 = big[i], i2 = big[j];
                        ans[i1] = ans[i2] = 4;
                    }
                }
            }
            a = i1, b = i2;

            if (!~a) {
                cout << "! -1" << endl;
                return 0;
            }
        }
        for (int i = 1; i <= n; i++) if (!ans[i]) {
            int x = query(a, b, i);
            auto &xs = dp[ans[a]];
            ans[i] = find(xs + 1, xs + 5, x) - xs;
        }
        cout << "! ";
        for (int i = 1; i <= n; i++) cout << ans[i] << " ";
        cout << endl;
    }

    return 0;
}
