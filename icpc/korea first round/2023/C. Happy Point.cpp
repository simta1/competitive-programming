#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    string st;
    getline(cin, st);

    string h = "HAPPY", g = "SAD";
    int ph = 0, pg = 0;
    for (auto ch : st) {
        if (h.find(ch) != string::npos) ++ph;
        if (g.find(ch) != string::npos) ++pg;
    }

    cout << fixed << setprecision(2);
    if (!ph && !pg) cout << 50.0;
    else cout << ph / double(ph + pg) * 100;

    return 0;
}
