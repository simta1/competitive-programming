#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	string st;
	cin >> st;

	int cnt[26]{};
	for (auto ch : st) ++cnt[ch - 'a'];
	cout << char(max_element(cnt, cnt + 26) - cnt + 'a');

	return 0;
}
