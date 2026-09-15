#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    map<string, array<int, 10>> mp;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 10; j++) {
            string st;
            cin >> st;
            ++mp[st][j];
        }
    }

    set<pair<pair<int, array<int, 10>>, string>> s;
    for (auto [st, cnt] : mp) {
        s.emplace(pair{accumulate(cnt.begin(), cnt.end(), 0), cnt}, st);
    }

    auto it = prev(s.end());
    auto [a1, b1] = *it;
    if (s.size() == 1) cout << b1;
    else {
        auto [a2, b2] = *--it;
        if (a1 == a2) cout << "tie";
        else cout << b1;
    }

    return 0;
}
