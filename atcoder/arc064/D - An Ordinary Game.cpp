#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	string st;
	cin >> st;

	if (st.size() - (st[0] == st.back()) & 1) cout << "First\n";
	else cout << "Second\n";

	return 0;
}
