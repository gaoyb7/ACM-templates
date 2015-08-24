struct edge { int v, f, nxt; };
edge e[maxn * maxn];
int g[maxn], h[maxn], vh[maxn];
int psz, esz, S, T;

void init(int n) {
    psz = 1; esz = n;
    memset(g, 0, sizeof(g));
}

void addedge(int u, int v, int f) {
    e[++psz] = (edge){v, f, g[u]}; g[u] = psz;
    e[++psz] = (edge){u, 0, g[v]}; g[v] = psz;
}

int aug(int u, int f) {
    if (u == T) return f;
    int d = f;
    for (int i = g[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if (e[i].f && h[u] == h[v] + 1) {
            int ff = aug(v, min(e[i].f, d));
            e[i].f -= ff; e[i ^ 1].f += ff; d -= ff;
            if (h[S] == esz || !d) return f - d;
        }
    }
    int w = d < f ? min(esz, h[u] + 2) : esz;
    for (int i = g[u]; i; i = e[i].nxt)
        if (e[i].f)
            w = min(w, h[e[i].v] + 1);
    ++vh[w];
    --vh[h[u]] ? h[u] = w : h[S] = esz;
    return f - d;
}

int maxflow() {
    memset(h, 0, sizeof(h));
    memset(vh, 0, sizeof(vh));
    vh[0] = esz;
    int ret = 0;
    while (h[S] != esz)
        ret += aug(S, inf);
    return ret;
}
