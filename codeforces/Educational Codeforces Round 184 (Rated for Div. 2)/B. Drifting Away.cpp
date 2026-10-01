#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		string st;
		cin >> st;

		int n = st.size();
		int l = 0;
		while (l < n && st[l] == '<') ++l;

		int r = n - 1;
		while (r >= 0 && st[r] == '>') --r;

		if (l < r) cout << "-1\n";
		else {
			if (l < n && st[l] == '*') ++l;
			if (r >= 0 && st[r] == '*') --r;
			cout << max(l, n - 1 - r) << "\n";
		}
	}

	return 0;
}
