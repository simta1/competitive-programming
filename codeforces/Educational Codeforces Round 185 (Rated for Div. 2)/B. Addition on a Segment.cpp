#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n;
		cin >> n;

		multiset<int> s;
		for (int _ = n; _--;) {
			int x;
			cin >> x;
			if (x) s.insert(x);
		}

		for (int _ = n - 1; _--;) {
			int x = *s.rbegin();
			s.erase(--s.end());
			s.insert(x - 1);
		}

		int ans = 0;
		for (auto e : s) ans += !!e;
		cout << ans << "\n";
	}

	return 0;
}
