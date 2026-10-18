#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool check(const string &st, string &target) {
    string res;
    for (int i = 0, j = 0; i < st.size(); i = j) {
        while (j < st.size() && st[i] == st[j]) ++j;
        int cnt = j - i;
        if (cnt > 9) return false;
        res += to_string(cnt);
        res += st[i];
    }
    return res == target;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    string st;
    cin >> st;

    int n = st.size();

    if (n & 1) {
        cout << -1;
        return 0;
    }

    string ans;
    for (int i = 0; i < n; i += 2) {
        int cnt = st[i] - '0';
        ans += string(cnt, st[i + 1]);
    }

    if (check(ans, st) && ans[0] != '0') cout << ans;
    else cout << -1;

    return 0;
}
