#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        string st;
        cin >> st;

        vector<int> v;
        v.push_back(st[0] - '1');
        for (int i = 1; i < st.size(); i++) v.push_back(st[i] - '0');

        int sum = 0;
        for (auto ch : st) sum += ch - '0';
        sort(v.rbegin(), v.rend());

        int ans = 0;
        for (auto e : v) {
            if (sum <= 9) break;
            
            sum -= e;
            ++ans;
        }
        cout << ans << "\n";
    }

    return 0;
}
