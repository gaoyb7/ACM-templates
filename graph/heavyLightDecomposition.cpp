void dfs1(int u, int p, int d) {
	sz[u] = 1; son[u] = 0; dep[u] = d; fa[u] = p;
	for (int v: e[u]) {
		if (v == p) continue;
		dfs1(v, u, d + 1);
		sz[u] += sz[v];
		if (!son[u] || sz[v] > sz[son[u]]) son[u] = v;
	}
}

void dfs2(int u, int p) {
	top[u] = p; pos[u] = ++cnt; ori[cnt] = u;
	if (!son[u]) return;
	dfs2(son[u], p);
	for (int v: e[u])
		if (v != fa[u] && v != son[u]) dfs2(v, v);
}
