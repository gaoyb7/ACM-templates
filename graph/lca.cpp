//LCA offline
void dfs(int u) {
	vis[u] = true;
	for (size_t i = 0; i < q[u].size(); ++i) {
		int v = q[u][i].first, id = q[u][i].second;
		if (vis[v]) ans[id] = find(v);
	}
	for (int v: e[u])
		if (!vis[v])
			dfs(v), fa[v] = u;
}

//LCA online
void dfs(int u) {
	for (int i = 0; i < DEP; ++i) 
		fa[u][i + 1] = fa[fa[u][i]][i];
	for (int v: e[u])
		if (v != fa[u][0])
			fa[v][0] = u, dep[v] = dep[u] + 1, dfs(v);
}

int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	for (int i = DEP; i >= 0; --i) {
		if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
	}
	if (u == v) return u;
	for (int i = DEP; i >= 0; --i) {
		if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	}
	return fa[u][0];
}
