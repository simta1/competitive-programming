#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

pll f(int n, int k) {
    ll a = 90 * n + (k - 1) * 360;
    ll b = n;
    ll g = __gcd(a, b);
    return {a / g, b / g};
}

struct cmp {
    bool operator()(const array<ll, 4> &bot, const array<ll, 4> &top) const {
        return bot[0] * top[1] > bot[1] * top[0];
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    priority_queue<array<ll, 4>, vector<array<ll, 4>>, cmp> pq;
    for (int i = 1864; i <= 1909; i++) pq.push({90, 1, i, 1});

    ll ans = 0;
    pll prv = {0, 1};
    while (!pq.empty()) {
        auto [a, b, n, k] = pq.top();
        pq.pop();

        pll cur = {a, b};
        if (prv != cur) {
            prv = cur;
            ++ans;
        }

        if (k < n) {
            auto [a, b] = f(n, k + 1);
            pq.push({a, b, n, k + 1});
        }
    }

    cout << ans;

    return 0;
}
