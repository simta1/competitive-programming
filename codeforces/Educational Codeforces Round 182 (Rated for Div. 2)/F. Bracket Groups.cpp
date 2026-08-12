#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Aho {
    struct Node {
        int mp[2] = {-1, -1}, go[2] = {-1, -1};
        int fail = 0;
        bool end = false;
    };
    vector<Node> tree = {Node()};
    int charToIdx(char ch) { return ch == ')'; }
    void insert(const string &st) {
        int cur = 0;
        for (auto ch : st) {
            int i = charToIdx(ch);
            if (!~tree[cur].mp[i]) {
                tree[cur].mp[i] = tree.size();
                tree.emplace_back();
            }
            cur = tree[cur].mp[i];
        }
        tree[cur].end = true;
    }
    void build() {
        queue<int> q;
        for (int i = 0; i < 2; i++) {
            int nxt = tree[0].mp[i];
            if (!~nxt) tree[0].go[i] = 0;
            else {
                tree[0].go[i] = nxt;
                q.push(nxt);
            }
        }
        while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            tree[cur].end |= tree[tree[cur].fail].end;
            for (int i = 0; i < 2; i++) {
                int nxt = tree[cur].mp[i];
                if (!~nxt) {
                    tree[cur].go[i] = tree[tree[cur].fail].go[i];
                }
                else {
                    tree[cur].go[i] = nxt;
                    tree[nxt].fail = tree[tree[cur].fail].go[i];
                    q.push(nxt);
                }
            }
        }
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    Aho aho;
    vector<string> v(n);
    for (auto &st : v) {
        cin >> st;
        if (st == "()") {
            cout << -1;
            return 0;
        }
        aho.insert(st);
    }
    aho.build();

    vector dp(k + 1, vector(aho.tree.size(), vector<bool>(k / 2 + 1))); // dp[len][state][bal]
    dp[0][0][0] = 1;
    vector prv(k + 1, vector(aho.tree.size(), vector<array<int, 3>>(k / 2 + 1))); // {ch, pstate, pbal}
    int state = -1;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < aho.tree.size(); j++) {
            for (int bal = 0; bal <= k / 2; bal++) {
                if (!dp[i][j][bal]) continue;
                for (int ch = 0; ch < 2; ch++) {
                    int nj = aho.tree[j].go[ch];
                    int nbal = bal + (ch == 0 ? 1 : -1);
                    if (!aho.tree[nj].end && nbal >= 0 && nbal <= k / 2) {
                        dp[i + 1][nj][nbal] = 1;
                        prv[i + 1][nj][nbal] = {ch, j, bal};
                        if (i + 1 == k && nbal == 0) state = nj;
                    }
                }
            }
        }
    }

    if (~state) {
        string ans;
        int len = k, bal = 0;
        while (len) {
            auto [ch, pstate, pbal] = prv[len][state][bal];
            ans += "()"[ch == 1];
            --len;
            state = pstate;
            bal = pbal;
        }
        reverse(ans.begin(), ans.end());
        cout << "1\n" << ans << "\n" << n << "\n";
        for (int i = 1; i <= n; i++) cout << i << " ";
    }
    else {
        vector<int> a, b;
        for (int i = 0; i < n; i++) {
            auto &st = v[i];
            bool flag = false;
            for (int j = 1; j < st.size(); j++) {
                if (st[j - 1] == st[j]) flag = true;
            }
            if (flag) a.push_back(i + 1);
            else b.push_back(i + 1);
        }
        cout << "2\n";
        // a : ()..()
        for (int i = 0; i < k / 2; i++) cout << "()";
        cout << "\n" << a.size() << "\n";
        for (auto e : a) cout << e << " ";
        cout << "\n";
        // b : ((..))
        cout << string(k / 2, '(') << string(k / 2, ')') << "\n";
        cout << b.size() << "\n";
        for (auto e : b) cout << e << " ";
        cout << "\n";
    }

    return 0;
}
