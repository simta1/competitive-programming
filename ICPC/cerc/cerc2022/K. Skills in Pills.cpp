#include <bits/stdc++.h>
using namespace std;
using ll = long long;

array<ll, 3> egcd(ll a, ll b) { // ax+by=g
    if (b == 0) return {1, 0, a};
    auto [x, y, g] = egcd(b, a % b);
    return {y, x - (a / b) * y, g};
};

ll eg2(ll a, ll b) { // min(ax = 1 + by)
    assert(a > 0);
    assert(b > 0);
    assert(__gcd(a, b) == 1);
    auto [x, y, g] = egcd(a, b);
    
    if (x < 1) {
        // x + bk >= 1
        // bk >= 1 - x
        // bk > -x
        ll k = (-x) / b + 1;
        x += b * k;
    }
    else {
        // x - bk >= 1
        // bk <= x - 1
        ll k = (x - 1) / b;
        x -= b * k;
    }
    return a * x;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    ll a, b, n;
    cin >> a >> b >> n;

    if (a == b) {
        cout << (n / a) + (n + 1) / a;
        return 0;
    }

    ll g = __gcd(a, b);
    ll lcm = a / g * b;
    if (lcm > n) {
        cout << n / a + n / b;
        return 0;
    }

    vector<int> dp(n + 1, -1);
    constexpr int INF = 1e8;
    auto f = [&](auto &&f, int cur) -> int {
        // cout << cur << "::\n";
        if (g >= 2) {
            return min(cur / a + (cur - 1) / b + 1, cur / b + (cur - 1) / a + 1);
        }
        if (cur < 0) return 0;
        if (cur == 1) return 1;

        auto &res = dp[cur];
        if (~res) return res;

        res = INF;
        ll ta = a, tb = b;
        ll nxt = eg2(ta, tb);
        // cout << ta << " " << tb << " " << nxt << "@\n";
        int val = nxt > cur ? (cur / ta + (cur - 1) / tb + 1) : (nxt / ta - 1 + (nxt - 1) / tb + 1 + f(f, cur - nxt + 1));
        res = val;

        swap(ta, tb);
        nxt = eg2(ta, tb);
        val = nxt > cur ? (cur / ta + (cur - 1) / tb + 1) : (nxt / ta - 1 + (nxt - 1) / tb + 1 + f(f, cur - nxt + 1));
        res = min(res, val);
        return res;
    };

    // eg2(2, 3);
    // cout << f(f, 6) << "::\n";
    cout << lcm / a - 1 + lcm / b - 1 + 1 + f(f, n - lcm + 1);

    return 0;
}
