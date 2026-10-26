#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		string st;
		cin >> st;

		if ([&]() {
			int len = 0;
			int unsorted = 0;
			int sorted = 0;
			for (auto ch : st) {
				assert(unsorted <= len);
				assert(sorted <= len);
				if (ch == '+') {
					++len;
				}
				else if (ch == '-') {
					--len;
					if (len < unsorted) unsorted = 0;
					if (len < sorted) sorted = len;
				}
				else if (ch == '0') {
					if (len < 2 || sorted == len) return false;
					if (!unsorted) unsorted = len;
				}
				else {
					if (len >= 2 && unsorted) return false;
					sorted = len;
				}
			}
			return true;
		}()) cout << "YES\n";
		else cout << "NO\n";
	}

	return 0;
}
