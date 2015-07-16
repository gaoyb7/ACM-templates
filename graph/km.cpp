int n;
int w[maxn][maxn];
int lx[maxn], ly[maxn], match[maxn], slack[maxn];
bool vx[maxn], vy[maxn];

bool dfs(int i) {
    vx[i] = true;
    for (int j = 0; j < n; ++j) {
        if (lx[i] + ly[j] > w[i][j]) {
            slack[j] = min(slack[j], lx[i] + ly[j] - w[i][j]);
        } else if (!vy[j]) {
            vy[j] = true;
            if (match[j] < 0 || dfs(match[j])) {
                match[j] = i;
                return true;
            }
        }
    }
    return false;
}

void km() {
    memset(match , -1, sizeof(match));
    memset(ly, 0, sizeof(ly));
    for (int i = 0; i < n; ++i)
        lx[i] = *max_element(w[i], w[i] + n);
    for (int i = 0; i < n; ++i) {
        for (;;) {
            memset(vx, 0, sizeof(vx));
            memset(vy, 0, sizeof(vy));
            memset(slack , 0x3f, sizeof(slack));
            if (dfs(i)) break;
            int d = inf;
            for (int i = 0; i < n; ++i) if (!vy[i]) d = min(d, slack[i]);
            for (int i = 0; i < n; ++i) {
                if (vx[i]) lx[i] -= d;
                if (vy[i]) ly[i] += d;
            }
        }
    }
}
