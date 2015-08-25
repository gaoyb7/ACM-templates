#include <cstdio>
#include <cstring>
#include <algorithm>
#include <deque>
using namespace std;

struct edge { int v, f, c, nxt; };
edge e[maxm];
int g[maxn], d[maxn];
int psz, esz, S, T, cost, dist;
bool vis[maxn];

void init(int n) {
    psz = 1; esz = n;
    memset(g, 0, sizeof(g));
    cost = dist = 0;
}

void add_edge(int u, int v, int f, int c) {
    e[++psz] = (edge){v, f, c, g[u]}; g[u] = psz;
    e[++psz] = (edge){u, 0, -c, g[v]}; g[v] = psz;
}

int aug(int u, int f) {
    if (u == T) return cost += dist * f, f;
    int d = f;
    vis[u] = true;
    for (int i = g[u]; i; i = e[i].nxt)
        if (e[i].f && !e[i].c && !vis[e[i].v]) {
            int f = aug(e[i].v, min(d, e[i].f));
            e[i].f -= f; e[i ^ 1].f += f; d -= f;
            if (!d) break;
        }
    return f - d;
}

bool modlabel() {
    deque<int> que;
    memset(vis, 0, sizeof(vis));
    memset(d, 0x3f, sizeof(d));
    que.push_back(S); d[S] = 0; vis[S] = true;
    while (!que.empty()) {
        int u = que.front(); que.pop_front(); vis[u] = false;
        for (int i = g[u]; i; i = e[i].nxt) {
            int v = e[i].v;
            if (e[i].f && d[u] + e[i].c < d[v]) {
                d[v] = d[u] + e[i].c;
                if (!vis[v]) {
                    if (que.empty() || d[v] < d[que.front()])
                        que.push_front(v);
                    else
                        que.push_back(v);
                    vis[v] = true;
                }
            }
        }
    }
    if (d[T] == inf) return false;
    for (int i = 0; i < esz; ++i)
        for (int j = g[i]; j; j = e[j].nxt)
            e[j].c += d[i] - d[e[j].v];
    dist += d[T];
    return true;
}

int min_cost(int &flow) {
    int tmp;
    flow = 0;
    while (modlabel()) {
        do {
            memset(vis, 0, sizeof(vis));
            flow += (tmp = aug(S, inf));
        } while (tmp);
    }
    return cost;
}
