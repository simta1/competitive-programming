#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int w;
    cin >> w;

    int ans = 0;
    auto f = [&](auto &&f) -> int {
        int m, n;
        cin >> m >> n;

        vector<int> v;
        ll sum = 0;
        while (n--) {
            int x = f(f);
            v.push_back(x);
            sum += x;
        }
        sort(v.begin(), v.end());
        while (sum > w) {
            sum -= v.back();
            v.pop_back();
            ++ans;
        }
        m += sum;

        ans += m / w;
        return m % w;
    };
    ans += bool(f(f));

    cout << ans << "\n";

    return 0;
}
