#include <bits/stdc++.h>
using namespace std;
using ll = long long;

tuple<ll, ll, ll> egcd(ll a, ll b) { // ax + by = gcd(a, b)
    if (b == 0) return {1, 0, a};
    auto [x, y, g] = egcd(b, a % b);
    return {y, x - (a / b) * y, g};
}
ll modInv(ll a, ll b) {
    auto [x, y, g] = egcd(a, b);
    return g != 1 ? -1 : (x + b) % b;
} // modInv(n, MOD)

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    ll n, q;
    cin >> n >> q;

    ll a = 0, b = 1, k = n;
    vector<int> v(n);
    iota(v.begin(), v.end(), 0);

    // 사람 v[i]가 a + bi (mod n)의자에 위치
    // g = gcd(b, n)
    // k = n / g 명의 사람만 살아있음
    while (q--) {
        char op;
        ll x;
        cin >> op >> x;
        if (x == n) x = 0;

        if (op == '+') {
            a += x;
            if (a >= n) a -= n;
        }
        else if (op == '*') {
            ll na = a * x % n;
            ll nb = b * x % n;
            ll g = __gcd(k, x);
            if (g == 1) {
                a = na, b = nb;
                continue;
            }

            int nk = k / g;
            vector<int> nv(nk);
            for (int i = 0; i < nk; i++) {
                int cur = (na + i * nb) % n;
                int mn = 1e9, idx = -1;
                for (int pi = i; pi < k; pi += nk) {
                    int prv = (a + b * pi) % n;
                    int dist = prv <= cur ? (cur - prv) : (cur + n - prv);
                    if (mn > dist) {
                        mn = dist;
                        idx = pi;
                    }
                }
                assert(~idx);
                nv[i] = v[idx];
            }
            a = na, b = nb, k = nk, v = nv;
        }
        else {
            ll g = n / k;
            assert(__gcd(b, n) == g);
            // a + bi === x (mod n)
            ll r = x - a;
            if (r < 0) r += n;

            // bi === r (mod n), 
            if (r % g) cout << "-1\n";
            else {
                // b/g i === r/g (mod n/g), (n/g=k임)
                int i = (r / g) * modInv(b / g, n / g) % (n / g);
                // 0 <= i < k
                cout << (v[i] == 0 ? n : v[i]) << "\n";
            }
        }
    }

    return 0;
}
