#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		string st;
		cin >> st;

		if (st.find('3') < st.find('1')) cout << "31\n";
		else cout << "13\n";
	}

	return 0;
}
