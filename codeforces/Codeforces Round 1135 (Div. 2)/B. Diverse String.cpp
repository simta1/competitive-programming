#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n, k;
		cin >> n >> k;

		string st;
		cin >> st;

		int cnt[2]{};
		for (auto ch : st) ++cnt[ch - '0'];

		ll a = cnt[0], b = cnt[1];
		if (a > b) swap(a, b);
		b = min<ll>(n, b + k);
		a = n - b;
		// cout << a << " " << b << "::\n";

		cout << (a * (a + 1) + b * (b + 1)) / 2 + 1 << "\n";
	}

	return 0;
}
