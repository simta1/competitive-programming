#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int a = 0, b = 0, c = 0, d = 0;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			char ch;
			cin >> ch;
			if (ch == 'A') {
				a = i, b = j;
	// cout << a << " " << b << " " << c << " " << d << "\n";
			}
			else if (ch == 'D') {
				c = i, d = j;
	// cout << a << " " << b << " " << c << " " << d << "\n";
			}
		}
	}

	// cout << a << " " << b << " " << c << " " << d << "\n";
	if (a == c && b != d || a != c && b == d) cout << "Yes\n";
	else cout << "No\n";

	return 0;
}
