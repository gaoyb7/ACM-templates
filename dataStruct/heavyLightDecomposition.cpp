void dfs1(int u, int p, int d) {
    sz[u] = 1; son[u] = 0; dep[u] = d; fa[u] = p;
    for (size_t i = 0; i < e[u].size(); ++i) {
        int v = e[u][i];
        if (v == p) continue;
        dfs1(v, u, d + 1);
        sz[u] += sz[v];
        if (!son[u] || sz[v] > sz[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int p) {
    top[u] = p; tree[u] = ++cnt; pre[cnt] = u;
    if (!son[u]) return;
    dfs2(son[u], p);
    for (size_t i = 0; i < e[u].size(); ++i) {
        int v = e[u][i];
        if (v != fa[u] && v != son[u]) dfs2(v, v);
    }
}
