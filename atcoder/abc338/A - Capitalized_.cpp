#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	string st;
	cin >> st;

	if ([&]() {
		if (st[0] >= 'a' && st[0] <= 'z') return false;
		for (int i = 1; i < st.size(); i++) {
			if (st[i] >= 'A' && st[i] <= 'Z') return false;
		}
		return true;
	}()) cout << "Yes\n";
	else cout << "No\n";

	return 0;
}
