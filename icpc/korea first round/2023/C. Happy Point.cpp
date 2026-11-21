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

	cout << setfill('0');
    if (!ph && !pg) cout << "50.00";
    else {
		ll a = ph * 10000;
		ll b = ph + pg;
		ll ans = (a + b / 2) / b;
		cout << ans / 100 << "." << setw(2) << ans % 100;
	}

    return 0;
}
