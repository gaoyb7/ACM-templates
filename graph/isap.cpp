struct edge { int v, f, nxt; };
edge e[maxn * maxn];
int g[maxn], h[maxn], vh[maxn];
int esz, vsz, S, T;

void init(int n) {
    esz = 1; vsz = n;
    memset(g, 0, sizeof(g));
}

void add_edge(int u, int v, int f) {
    e[++esz] = (edge){v, f, g[u]}; g[u] = esz;
    e[++esz] = (edge){u, 0, g[v]}; g[v] = esz;
}

int aug(int u, int f) {
    if (u == T) return f;
    int d = f;
    for (int i = g[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if (e[i].f && h[u] == h[v] + 1) {
            int ff = aug(v, min(e[i].f, d));
            e[i].f -= ff; e[i ^ 1].f += ff; d -= ff;
            if (h[S] == vsz || !d) return f - d;
        }
    }
    int w = d < f ? min(vsz, h[u] + 2) : vsz;
    for (int i = g[u]; i; i = e[i].nxt)
        if (e[i].f)
            w = min(w, h[e[i].v] + 1);
    ++vh[w];
    --vh[h[u]] ? h[u] = w : h[S] = vsz;
    return f - d;
}

int max_flow() {
    memset(h, 0, sizeof(h));
    memset(vh, 0, sizeof(vh));
    vh[0] = vsz;
    int ret = 0;
    while (h[S] != vsz)
        ret += aug(S, inf);
    return ret;
}
