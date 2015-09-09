struct edge { int v, f, nxt; } e[maxe];
int g[maxn], dist[maxn];
queue<int> que;
int n, sz, S, T;

void init() {
    memset(g, 0, sizeof(g));
    sz = 1;
}

void add_edge(int u, int v, int c) {
    e[++sz] = (edge){v, c, g[u]}; g[u] = sz;
    e[++sz] = (edge){u, 0, g[v]}; g[v] = sz;
}

bool bfs() {
    memset(dist, -1, sizeof(dist));
    while (!que.empty()) que.pop();
    dist[S] = 0;
    que.push(S);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int i = g[u]; i; i = e[i].nxt)
            if (e[i].f && dist[e[i].v] == -1) {
                que.push(e[i].v);
                dist[e[i].v] = dist[u] + 1;
            }
    }
    return dist[T] != -1;
}

int aug(int u, int delta) {
    if (u == T || delta == 0) return delta;
    int ret = 0;
    for (int i = g[u]; delta && i; i = e[i].nxt)
        if (e[i].f && dist[e[i].v] == dist[u] + 1) {
            int dd = aug(e[i].v, min(e[i].f, delta));
            e[i].f -= dd;
            e[i ^ 1].f += dd;
            delta -= dd;
            ret += dd;
        }
    if (!ret) dist[u] = -1;
    return ret;
}

int max_flow() {
    int ret = 0;
    while (bfs()) ret += aug(S, inf);
    return ret;
}
