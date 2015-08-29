// Hdu 3311
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#define V first
#define W second
using namespace std;

typedef pair<int, int> Pii;
const int maxn = 1000 + 10;
const int inf = 0x3f3f3f3f;
vector<Pii> e[maxn];
queue<Pii> que;
int dp[maxn][1 << 7];
bool inq[maxn][1 << 7];
int n, m, p;

void init() {
    for (int i = 0; i <= n + m; ++i) e[i].clear();
    for (int i = 1; i <= n + m; ++i) {
        int x;
        scanf("%d", &x);
        e[0].push_back(Pii(i, x));
        e[i].push_back(Pii(0, x));
    }
    while (p--) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        e[u].push_back(Pii(v, w));
        e[v].push_back(Pii(u, w));
    }
}

void spfa() {
    while (!que.empty()) {
        int st = que.front().second;
        int u = que.front().first;
        que.pop();
        inq[u][st] = false;
        for (size_t i = 0; i < e[u].size(); ++i) {
            int v = e[u][i].V, w = e[u][i].W;
            if (dp[u][st] + w < dp[v][st]) {
                dp[v][st] = dp[u][st] + w;
                if (!inq[v][st]) {
                    inq[v][st] = true;
                    que.push(Pii(v, st));
                }
            }
        }
    }
}

void work() {
    memset(dp, 0x3f, sizeof(dp));
    memset(inq, 0, sizeof(inq));
    for (int i = 0; i <= n; ++i) dp[i][1 << i] = 0;

    int limit = 1 << (n + 1);
    for (int i = 0; i < limit; ++i) {
        for (int j = 0; j <= n + m; ++j) {
            for (int st = i; st; st = (st - 1) & i)
                dp[j][i] = min(dp[j][i], dp[j][st] + dp[j][i - st]);
            if (dp[j][i] < inf)
                que.push(Pii(j, i)), inq[j][i] = true;
        }
        spfa();
    }
    printf("%d\n", dp[0][limit - 1]);
}

int main() {
    while (scanf("%d%d%d", &n, &m, &p) == 3) {
        init();
        work();
    }
}
