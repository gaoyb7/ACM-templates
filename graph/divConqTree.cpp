//poj 1741
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define V first
#define W second
using namespace std;

const int maxn = 10000 + 10;
typedef pair<int, int> Pii;
vector<Pii> e[maxn];
vector<int> dep;
int f[maxn], s[maxn], d[maxn];
bool vis[maxn];
int n, k, root, sz, ans;

void getroot(int u, int fa) {
    s[u] = 1;
    f[u] = 0;
    for (size_t i = 0; i < e[u].size(); ++i) {
        int v = e[u][i].V;
        if (v == fa || vis[v]) continue;
        getroot(v, u);
        s[u] += s[v];
        f[u] = max(f[u], s[v]);
    }
    f[u] = max(f[u], sz - s[u]);
    if (f[u] < f[root]) root = u;
}

void getdep(int u, int fa) {
    dep.push_back(d[u]);
    for (size_t i = 0; i < e[u].size(); ++i) {
        int v = e[u][i].V;
        if (v == fa || vis[v]) continue;
        d[v] = d[u] + e[u][i].W;
        getdep(v, u);
    }
}

int calc(int u, int add) {
    int ret = 0;
    dep.clear();
    d[u] = add;
    getdep(u, 0);
    sort(dep.begin(), dep.end());
    for (int l = 0, r = dep.size() - 1; l < r;)
        if (dep[l] + dep[r] <= k) ret += r - l++;
        else --r;
    return ret;
}

void work(int u) {
    ans += calc(u, 0);
    vis[u] = true;
    for (size_t i = 0; i < e[u].size(); ++i) {
        int v = e[u][i].V;
        if (vis[v]) continue;
        ans -= calc(v, e[u][i].W);
        f[0] = sz = s[v];
        getroot(v, root = 0);
        work(root);
    }
}

int main() {
    while (scanf("%d%d", &n, &k) == 2 && n) {
        for (int i = 1; i <= n; ++i) e[i].clear();
        memset(vis, 0, sizeof(vis));

        for (int i = 1; i < n; ++i) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            e[u].push_back(Pii(v, w));
            e[v].push_back(Pii(u, w));
        }
        f[0] = sz = n;
        getroot(1, root = 0);
        ans = 0;
        work(root);
        printf("%d\n", ans);
    }
}

