struct edge { int v, f, nxt; };
const int maxn = 1000 + 10, maxm = 110000, inf = 0x3f3f3f3f;
int g[maxn], dist[maxn], nume, n, src, sink;
queue<int> que;
edge e[maxm];

void init() {
    memset(g, 0, sizeof(g));
    nume = 1;
}

void addedge(int u, int v, int c) {
    e[++nume] = (edge){v, c, g[u]}; g[u] = nume;
    e[++nume] = (edge){u, 0, g[v]}; g[v] = nume;
}

bool bfs() {
    memset(dist, -1, sizeof(dist));
    while (!que.empty()) que.pop();
    dist[src] = 0;
    que.push(src);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int i = g[u]; i; i = e[i].nxt)
            if (e[i].f && dist[e[i].v] == -1) {
                que.push(e[i].v);
                dist[e[i].v] = dist[u] + 1;
            }
    }
    return dist[sink] != -1;
}

int dfs(int u, int delta) {
    if (u == sink || delta == 0) return delta;
    int ret = 0;
    for (int i = g[u]; delta && i; i = e[i].nxt)
        if (e[i].f && dist[e[i].v] == dist[u] + 1) {
            int dd = dfs(e[i].v, min(e[i].f, delta));
            e[i].f -= dd;
            e[i ^ 1].f += dd;
            delta -= dd;
            ret += dd;
        }
    if (!ret) dist[u] = -1;
    return ret;
}

int maxflow() {
    int ret = 0;
    while (bfs()) ret += dfs(src, inf);
    return ret;
}
