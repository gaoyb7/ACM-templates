struct edge { int u, v, w; } e[maxn * maxn];

int f[maxn], pre[maxn], id[maxn], vis[maxn];
int n, m;

int chu_liu(int s) {
    int ret = 0;
    while (1) {
        memset(f, 0x3f, sizeof(f));
        for (int i = 0; i < m; ++i) {
            int u = e[i].u, v = e[i].v, w = e[i].w;
            if (v != u && w < f[v]) {
                f[v] = w;
                pre[v] = u;
            }
        }
        f[s] = 0;
        for (int i = 0; i < n; ++i)
            if (f[i] == inf) return -1;
        int cnt = 0;
        memset(id, -1, sizeof(id));
        memset(vis, -1, sizeof(vis));
        for (int i = 0; i < n; ++i) {
            ret += f[i];
            int v = i;
            while (vis[v] != i && v != s && id[v] == -1) {
                vis[v] = i;
                v = pre[v];
            }
            if (v != s && id[v] == -1) {
                for (int u = pre[v]; u != v; u = pre[u])
                    id[u] = cnt;
                id[v] = cnt++;
            }
        }
        if (!cnt) break;
        for (int i = 0; i < n; ++i)
            if (id[i] == -1) id[i] = cnt++;
        for (int i = 0; i < m; ++i) {
            int u = e[i].u, v = e[i].v;
            e[i].u = id[u]; e[i].v = id[v];
            if (e[i].u != e[i].v) e[i].w -= f[v];
        }
        s = id[s]; n = cnt;
    }
    return ret;
}

int min_branch(int s = -1) {
    if (s != -1) return chu_liu(s);
    int tot = 0;
    for (int i = 0; i < m; ++i)
        tot += e[i].w;
    for (int i = 0; i < n; ++i)
        e[m++] = (edge){n, i, tot};
    int ret = chu_liu(n++) - tot;
    return ret >= tot ? -1 : ret - tot;
}
