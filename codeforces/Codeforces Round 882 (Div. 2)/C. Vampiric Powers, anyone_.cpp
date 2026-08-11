#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
    Node *chd[2] = {0, 0};
    ~Node() {
        delete chd[0];
        delete chd[1];
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        Node *root = new Node();
        auto insert = [&](int x) {
            Node *cur = root;
            for (int i = 7; i >= 0; i--) {
                int bit = x >> i & 1;
                if (!cur->chd[bit]) cur->chd[bit] = new Node();
                cur = cur->chd[bit];
            }
        };

        auto mxquery = [&](int x) {
            Node *cur = root;
            for (int i = 7; i >= 0; i--) {
                int bit = x >> i & 1;
                if (cur->chd[!bit]) bit ^= 1;
                cur = cur->chd[bit];
                x ^= bit << i;
            }
            return x;
        };

        vector<int> v(n);
        for (auto &e : v) cin >> e;

        int pfx = 0, ans = 0;
        insert(pfx);
        for (auto e : v) {
            pfx ^= e;
            // cout << pfx << "\n";
            ans = max(ans, mxquery(pfx));
            insert(pfx);
        }
        cout << ans << "\n";
        delete root;

        // int mxSum = 0;
        // for (auto b : getXorBasis(v)) mxSum = max(mxSum, mxSum ^ b);
        // cout << mxSum << "\n";
    }

    return 0;
}
