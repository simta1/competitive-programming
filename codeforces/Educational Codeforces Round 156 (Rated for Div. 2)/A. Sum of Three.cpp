#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n;
		cin >> n;

		if (n <= 6) cout << "NO\n";
		else {
			if (n % 3) {
				cout << "YES\n";
				cout << "1 2 " << n - 3 << "\n";
			}
			else {
				if (n >= 10) {
					cout << "YES\n";
					cout << "1 4 " << n - 5 << "\n";
				}
				else cout << "NO\n";
			}
		}
	}

	return 0;
}
