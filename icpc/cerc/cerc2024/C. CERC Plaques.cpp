#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    
    int n;
    cin >> n;

    map<string, vector<string>> mp;
    for (int _ = n; _--;) {
        string st;
        cin >> st;
        mp[st.substr(0, 4)].push_back(st);
    }

    vector<string> ans;
    for (int _ = n; _--;) {
        string st;
        cin >> st;
        if (!mp.count(st.substr(0, 4)) || mp[st.substr(0, 4)].empty()) {
            cout << "NO";
            return 0;
        }
        else {
            auto &v = mp[st.substr(0, 4)];
            ans.push_back(v.back() + " " + st);
            v.pop_back();
        }
    }
    
    cout << "YES\n";
    for (auto &st : ans) cout << st << "\n";

	return 0;
}
