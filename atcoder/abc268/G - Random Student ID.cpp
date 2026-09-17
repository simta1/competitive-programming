#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Trie {
    struct Node {
        map<char, int> mp;
        int cnt = 0;
        int cnt2 = 0;
    };
    vector<Node> tr = {Node()};
    void insert(const string &st) { // O(N)
        int cur = 0;
        for (auto &e : st) {
            if (!tr[cur].mp.count(e)) {
                tr[cur].mp[e] = tr.size();
                tr.emplace_back();
            }
            cur = tr[cur].mp[e];
            ++tr[cur].cnt2;
        }
        ++tr[cur].cnt;
    }
    pair<int, int> count(const string &st) {
        int res = 0;
        int cur = 0;
        for (auto &e : st) {
            cur = tr[cur].mp[e];
            res += tr[cur].cnt;
        }
        return {res, tr[cur].cnt2};
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<string> v(n);
    for (auto &st : v) cin >> st;

    Trie trie;
    for (auto &st : v) trie.insert(st);

    constexpr ll MOD = 998'244'353;
    constexpr ll inv2 = MOD + 1 >> 1;

    for (auto &st : v) {
        auto [a, b] = trie.count(st);
        // cout << a << " " << n - a - b << "::\n";
        ll ans = (a + (n + 1 - a - b) * inv2) % MOD;
        cout << ans << "\n";
    }

    return 0;
}
