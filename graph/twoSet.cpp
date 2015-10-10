struct twoset {
	vector<int> e[maxn * 2];
	bool vis[maxn * 2];
	int s[maxn * 2], n, sz;

	bool dfs(int u) {
		if (vis[u ^ 1]) return false;
		if (vis[u]) return true;
		vis[u] = true;
		s[sz++] = u;
		for (size_t i = 0; i < e[u].size(); ++i)
			if (!dfs(e[u][i]))
				return false;
		return true;
	}

	void init(int n) {
		this->n = n;
		for (int i = 0; i < 2 * n; ++i) e[i].clear();
		memset(vis, 0, sizeof(vis));
	}

	void add_clause(int x, int xval, int y, int yval) {
		x = x * 2 + xval;
		y = y * 2 + yval;
		e[x ^ 1].push_back(y);
		e[y ^ 1].push_back(x);
	}

	bool solve() {
		for (int i = 0; i < 2 * n; i += 2)
			if (!vis[i] && !vis[i + 1]) {
				sz = 0;
				if (!dfs(i)) {
					while (sz) vis[s[--sz]] = false;
					if (!dfs(i + 1)) return false;
				}
			}
		return true;
	}
};
