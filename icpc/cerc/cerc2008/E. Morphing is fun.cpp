#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n;
		cin >> n;

		vector<string> v(n);
		for (auto &st : v) cin >> st;

		if (v[0][0] == 'a') {
			cout << "YES\n";
			continue;
		}

		vector<bool> visited(n);
		queue<int> q;
		for (int i = 0; i < n; i++) {
			auto &st = v[i];
			if (st.size() == 1 && st[0] - 'a' == i) {
				visited[i] = 1;
				q.push(i);
			}
		}

		vector<int> idx(n);
		while (!q.empty()) {
			q.pop();
			for (int nxt = 0; nxt < n; nxt++) if (!visited[nxt]) {
				auto &st = v[nxt];
				while (idx[nxt] < st.size() && visited[st[idx[nxt]] - 'a'] == 1) ++idx[nxt];
				if (idx[nxt] == st.size()) {
					visited[nxt] = 1;
					q.push(nxt);
				}
			}
		}

		if (visited[0]) {
			cout << "YES\n";
			continue;
		}

		vector<int> adj(n);
		for (int i = 0; i < n; i++) if (!visited[i]) {
			auto &st = v[i];
			adj[i] = st[idx[i]] - 'a';
		}

		bool ans = 0;
		vector<int> path, state(n);
		auto dfs = [&](auto &&dfs, int cur) -> void {
			state[cur] = 1;
			path.push_back(cur);

			int nxt = adj[cur];
			if (!state[nxt]) {
				dfs(dfs, nxt);
			}
			else if (state[nxt] == 1) {
				vector<int> cycle;
				for (int i = path.size() - 1; i >= 0; i--) {
					cycle.push_back(path[i]);
					if (path[i] == nxt) break;
				}

				if (cycle.size() == 1) ans = 1;
				else {
					for (auto e : cycle) if (idx[e] > 0) ans = 1;
				}
			}
			state[cur] = 2;
			path.pop_back();
		};
		dfs(dfs, 0);

		if (ans) cout << "YES\n";
		else cout << "NO\n";
	}

	return 0;
}
