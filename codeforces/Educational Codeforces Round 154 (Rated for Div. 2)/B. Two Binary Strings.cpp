#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		string a, b;
		cin >> a >> b;

		if ([&]() {
			for (int i = 1; i < a.size(); i++) {
				if (a[i - 1] == '0' && a[i] == '1' && b[i - 1] == '0' && b[i] == '1') return true;
			}
			return false;
		}()) cout << "YES\n";
		else cout << "NO\n";
	}

	return 0;
}
