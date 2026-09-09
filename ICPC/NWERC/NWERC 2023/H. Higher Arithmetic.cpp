#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> v(n);
    for (auto &e : v) cin >> e;
    sort(v.begin(), v.end());
    int one = count(v.begin(), v.end(), 1);
    int two = count(v.begin(), v.end(), 2);

    int c1 = one, c2 = two;
    vector<string> ans;

    if (n == 1) {
        cout << v[0] << "\n";
        return 0;
    }

    if (one == 1) {
        ans.push_back("(1+" + to_string(v[1]) + ")");
        for (int i = 2; i < n; i++) ans.push_back(to_string(v[i]));
    }
    else {
        int mn = min(c1, c2);
        c1 -= mn;
        c2 -= mn;
        while(mn--) ans.push_back("(1+2)");

        while (c1 > 4) {
            ans.push_back("(1+1+1)");
            c1 -= 3;
        }

        if (c1 == 4) {
            ans.push_back("(1+1)");
            ans.push_back("(1+1)");
        }
        else if (c1 == 3) ans.push_back("(1+1+1)");
        else if (c1 == 2) ans.push_back("(1+1)");
        else if (c1 == 1) {
            assert(!ans.empty());
            ans.back() = "(1+1+2)";
        }

        while (c2--) ans.push_back("2");
        for (int i = one + two; i < n; i++) ans.push_back(to_string(v[i]));
    }

    cout << ans[0];
    for (int i = 1; i < ans.size(); i++) cout << "*" << ans[i];
    return 0;
}
