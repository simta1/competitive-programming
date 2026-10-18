#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    
    vector<int> v(8);
    deque<int> dq(90);
    for (auto &e : v) cin >> e;
    for (auto &e : dq) cin >> e;

    vector<int> a = {1}, b = {1}, c = {100}, d = {100};
    auto f = [&]() {
        int put = -1;
        for (auto e : v) {
            if (e == a.back() - 10 || e == b.back() - 10 || e == c.back() + 10 || e == d.back() + 10) {
                put = e;
                break;
            }
        }
        if (~put) {
            if (a.back() - 10 == put) a.push_back(put);
            else if (b.back() - 10 == put) b.push_back(put);
            else if (c.back() + 10 == put) c.push_back(put);
            else if (d.back() + 10 == put) d.push_back(put);
            else assert(false);
            v.erase(find(v.begin(), v.end(), put));
            return true;
        }

        constexpr int INF = 1e8;
        int mn = INF;
        for (auto e : v) {
            int cur = INF;
            if (a.back() < e) cur = e - a.back();
            if (b.back() < e) cur = min(cur, e - b.back());
            if (c.back() > e) cur = min(cur, c.back() - e);
            if (d.back() > e) cur = min(cur, d.back() - e);
            mn = min(mn, cur);
        }
        if (mn == INF) return false;
        for (auto e : v) {
            int cur = INF;
            if (a.back() < e) cur = e - a.back();
            if (b.back() < e) cur = min(cur, e - b.back());
            if (c.back() > e) cur = min(cur, c.back() - e);
            if (d.back() > e) cur = min(cur, d.back() - e);
            if (cur == mn) {
                put = e;
                break;
            }
        }
        if (~put) {
            if (a.back() < put && put - a.back() == mn) a.push_back(put);
            else if (b.back() < put && put - b.back() == mn) b.push_back(put);
            else if (c.back() > put && c.back() - put == mn) c.push_back(put);
            else if (d.back() > put && d.back() - put == mn) d.push_back(put);
            else assert(false);
            v.erase(find(v.begin(), v.end(), put));
            return true;
        }
        return false;
    };

    while (!v.empty()) {
        if (!f()) break;
        if (!f()) break;

        if (!dq.empty()) {
            v.push_back(dq.front());
            dq.pop_front();
            v.push_back(dq.front());
            dq.pop_front();
        }
    }

    for (auto e : a) cout << e << " "; cout << "\n";
    for (auto e : b) cout << e << " "; cout << "\n";
    for (auto e : c) cout << e << " "; cout << "\n";
    for (auto e : d) cout << e << " "; cout << "\n";
    for (auto e : v) cout << e << " "; cout << "\n";
    for (auto e : dq) cout << e << " "; cout << "\n";

    return 0;
}
