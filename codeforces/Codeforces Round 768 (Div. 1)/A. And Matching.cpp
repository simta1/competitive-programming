#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    // constexpr int N = 8;
    // vector<int> v(N);
    // iota(v.begin(), v.end(), 0);
    // do {
    //     int sum = 0;
    //     for (int i = 0; i < N; i += 2) {
    //         sum += v[i] & v[i + 1];
    //     }
    //     if (sum == N - 1) {
    //         for (auto &e : v) cout << e << " "; cout << "\n";
    //     }
    // } while (next_permutation(v.begin(), v.end()));

    int TC;
    for (cin >> TC; TC--;) {
        int n, k;
        cin >> n >> k;

        if (n == 4 && k == 3) {
            cout << "-1\n";
            continue;
        }

        vector<bool> rm(n);
        vector<pair<int, int>> ans;
        if (k + 1 == n) {
            ans.emplace_back(n - 1, n - 2);
            ans.emplace_back(0, 1);
            rm[n - 1] = rm[n - 2] = rm[0] = rm[1] = 1;
            int a = 3;
            int b = n - 3;
            ans.emplace_back(a, b);
            ans.emplace_back(n - 1 - a, n - 1 - b);
            rm[a] = rm[b] = rm[n - 1 - a] = rm[n - 1 - b] = 1;
        }
        else {
            ans.emplace_back(k, n - 1);
            if (k) ans.emplace_back(n - 1 - k, 0);
            rm[k] = rm[n - 1] = rm[n - 1 - k] = rm[0] = 1;
        }

        for (int i = 0, j = n - 1; i < j; ++i, --j) {
            if (!rm[i] && !rm[j]) ans.emplace_back(i, j);
        }

        // assert([&]() {
        //     int sum = 0;
        //     for (auto [a, b] : ans) sum += a & b;
        //     if (sum != k || ans.size() != n / 2) return false;
        //     vector<bool> used(n);
        //     for (auto [a, b] : ans) {
        //         if (used[a] || used[b]) return false;
        //         used[a] = used[b] = 1;
        //     }
        //     return true;
        // }());
        for (auto [a, b] : ans) cout << a << " " << b << "\n";
    }

    return 0;
}
