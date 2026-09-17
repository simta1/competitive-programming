#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    string s, t;
    cin >> s >> t;

    if ([&]() {
        if (s.size() > t.size()) return false;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] != t[i]) return false;
        }
        return true;
    }()) cout << "Yes\n";
    else cout << "No\n";

    return 0;
}
