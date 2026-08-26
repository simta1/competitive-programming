#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int f(const string &st) {
    int n = st.size();
    int j = n / 2 - 1;
    while (j > 0 && st[j] == st[n - 1 - j]) --j;

    int cnt[26]{};
    for (int i = 0; i <= j; i++) {
        ++cnt[st[i] - 'a'];
        --cnt[st[n - 1 - i] - 'a'];
    }
    bool same = true;
    for (int i = 0; i < 26; i++) {
        if (cnt[i]) same = 0;
    }

    if (same) return j + 1;

    int idx = n / 2;
    int a[26]{}, b[26]{};
    for (int i = 0; i <= idx; i++) ++a[st[i] - 'a'];
    for (int i = idx + 1; i < n; i++) ++b[st[i] - 'a'];
    auto check = [&]() {
        for (int i = 0; i < 26; i++) {
            if (a[i] < b[i]) return false;
        }
        return true;
    };

    if (check()) return idx + 1;
    while (1) {
        ++idx;
        ++a[st[idx] - 'a'];
        --b[st[idx] - 'a'];
        if (check()) return idx + 1;
    }
    assert(false);
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        string st;
        cin >> st;

        int n = st.size();
        int i = 0;
        while (i < n / 2 && st[i] == st[n - 1 - i]) ++i;
        if (i == n / 2) {
            cout << "0\n";
            continue;
        }

        st = st.substr(i, n - 1 - i - i + 1);
        int ans = f(st);
        reverse(st.begin(), st.end());
        ans = min(ans, f(st));
        cout << ans << "\n";
    }

    return 0;
}
