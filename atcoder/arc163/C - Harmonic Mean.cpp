#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> f(int n) {
    vector<int> res;
    for (int i = 1; i < n; i++) res.push_back(i * (i + 1));
    res.push_back(n);
    return res;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        if (n == 2) {
            cout << "No\n";
        }
        else {
            cout << "Yes\n";
            if (n == 1) cout << "1\n";
            else {
                int sq = sqrt(n);
                vector<int> ans;
                if (sq * (sq + 1) != n) ans = f(n);
                else {
                    ans = f(n - 1);
                    for (auto &e : ans) e <<= 1;
                    ans.push_back(2);
                }
                for (auto &e : ans) cout << e << " ";
                cout << "\n";
            }
        }
    }

    return 0;
}
