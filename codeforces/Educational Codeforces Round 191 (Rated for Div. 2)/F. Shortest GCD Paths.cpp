// #include <bits/stdc++.h>
// using namespace std;
// using ll = long long;

// int main() {
//     cin.tie(0) -> sync_with_stdio(0);

//     int n, a, b;
//     cin >> n >> a >> b;

//     int g = __gcd(a, b);
//     a /= g, b /= g;

//     vector<int> da, db;
//     int i = 1;
//     for (; i < a / i; i++) {
//         da.push_back(i);
//         da.push_back(a / i);
//     }
//     if (i == a / i) da.push_back(i);

//     i = 1;
//     for (; i < b / i; i++) {
//         db.push_back(i);
//         db.push_back(b / i);
//     }
//     if (i == b / i) db.push_back(i);

//     sort(da.begin(), da.end());
//     sort(db.begin(), db.end());

//     int ta = da.size(), tb = db.size();
//     vector<int> ispA(ta), ispB(tb);
//     for (int i = 0; i < ta; i++) {
//         for (int j = 0; j <= i; j++) {
//             if (da[i] % da[j] == 0) ++ispA[i];
//         }
//         ispA[i] = ispA[i] <= 2;
//     }
//     for (int i = 0; i < tb; i++) {
//         for (int j = 0; j <= i; j++) {
//             if (db[i] % db[j] == 0) ++ispB[i];
//         }
//         ispB[i] = ispB[i] <= 2;
//     }

//     vector<vector<pair<int, int> > > pa(ta), pb(tb), pa2(ta), pb2(tb);
//     for (int i = 0; i < ta; i++) {
//         for (int j = 0; j <= i; j++) {
//             if (da[i] % da[j] == 0) {
//                 int mul = da[i] / da[j];
//                 if (ispA[lower_bound(da.begin(), da.end(), mul) - da.begin()]) pa2[j].emplace_back(i, da[i] / da[j]);
//                 else pa[j].emplace_back(i, da[i] / da[j]);
//             }
//         }
//     }
//     for (int i = 0; i < tb; i++) {
//         for (int j = 0; j <= i; j++) {
//             if (db[i] % db[j] == 0) {
//                 int mul = db[i] / db[j];
//                 if (ispB[lower_bound(db.begin(), db.end(), mul) - db.begin()]) pb2[j].emplace_back(i, db[i] / db[j]);
//                 else pb[j].emplace_back(i, db[i] / db[j]);
//             }
//         }
//     }

//     constexpr int INF = 2e9;
//     vector dp(ta, vector<int>(tb, INF));
//     dp[0][0] = 0;
//     for (int i = 0; i < ta; i++) {
//         for (int j = 0; j < tb; j++) {
//             if (dp[i][j] == INF) continue;
//             for (auto [ni, p] : pa[i]) {
//                 for (auto [nj, q] : pb2[j]) {
//                     dp[ni][nj] = min(dp[ni][nj], dp[i][j] + max(p, q));
//                 }
//             }
//             for (auto [ni, p] : pa2[i]) {
//                 for (auto [nj, q] : pb[j]) {
//                     dp[ni][nj] = min(dp[ni][nj], dp[i][j] + max(p, q));
//                 }
//             }
//             for (auto [ni, p] : pa2[i]) {
//                 for (auto [nj, q] : pb2[j]) {
//                     dp[ni][nj] = min(dp[ni][nj], dp[i][j] + max(p, q));
//                 }
//             }
//         }
//     }
//     cout << dp[ta - 1][tb - 1];

//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, a, b;
    cin >> n >> a >> b;

    int g = __gcd(a, b);
    a /= g, b /= g;

    vector<int> da, db;
    int i = 1;
    for (; i < a / i; i++) if (a % i == 0) {
        da.push_back(i);
        da.push_back(a / i);
    }
    if (a % i == 0 && i == a / i) da.push_back(i);

    i = 1;
    for (; i < b / i; i++) if (b % i == 0) {
        db.push_back(i);
        db.push_back(b / i);
    }
    if (b % i == 0 && i == b / i) db.push_back(i);

    sort(da.begin(), da.end());
    sort(db.begin(), db.end());

    int ta = da.size(), tb = db.size();
    vector<int> ispA(ta), ispB(tb);
    for (int i = 0; i < ta; i++) {
        for (int j = 0; j <= i; j++) {
            if (da[i] % da[j] == 0) ++ispA[i];
        }
        ispA[i] = ispA[i] <= 2;
    }
    for (int i = 0; i < tb; i++) {
        for (int j = 0; j <= i; j++) {
            if (db[i] % db[j] == 0) ++ispB[i];
        }
        ispB[i] = ispB[i] <= 2;
    }

    vector<vector<pair<int, int> > > pa(ta), pb(tb), pa2(ta), pb2(tb);
    for (int i = 0; i < ta; i++) {
        for (int j = 0; j <= i; j++) {
            if (da[i] % da[j] == 0) {
                int mul = da[i] / da[j];
                if (ispA[lower_bound(da.begin(), da.end(), mul) - da.begin()]) pa2[j].emplace_back(i, da[i] / da[j]);
                else pa[j].emplace_back(i, da[i] / da[j]);
            }
        }
    }
    for (int i = 0; i < tb; i++) {
        for (int j = 0; j <= i; j++) {
            if (db[i] % db[j] == 0) {
                int mul = db[i] / db[j];
                if (ispB[lower_bound(db.begin(), db.end(), mul) - db.begin()]) pb2[j].emplace_back(i, db[i] / db[j]);
                else pb[j].emplace_back(i, db[i] / db[j]);
            }
        }
    }

    constexpr int INF = 2e9;
    vector dp(ta, vector<int>(tb, INF));
    dp[0][0] = 0;
    for (int i = 0; i < ta; i++) {
        for (int j = 0; j < tb; j++) {
            if (dp[i][j] == INF) continue;
            for (auto [ni, p] : pa[i]) {
                for (auto [nj, q] : pb2[j]) {
                    dp[ni][nj] = min(dp[ni][nj], dp[i][j] + max(p, q));
                }
            }
            for (auto [ni, p] : pa2[i]) {
                for (auto [nj, q] : pb[j]) {
                    dp[ni][nj] = min(dp[ni][nj], dp[i][j] + max(p, q));
                }
            }
            for (auto [ni, p] : pa2[i]) {
                for (auto [nj, q] : pb2[j]) {
                    dp[ni][nj] = min(dp[ni][nj], dp[i][j] + max(p, q));
                }
            }
        }
    }
    cout << dp[ta - 1][tb - 1];

    return 0;
}

