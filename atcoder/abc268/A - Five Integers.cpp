#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    vector<int> v(5);
    for (auto &e : v) cin >> e;

    sort(v.begin(), v.end());

    v.erase(unique(v.begin(), v.end()), v.end());
    cout << v.size();
    

    

    return 0;
}
