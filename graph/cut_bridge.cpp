int dfs(int u, int fa) {
    int lowu = pre[u] = ++clk;
    int child = 0;
    for (size_t i = 0; i < e[u].size(); ++i) {
        int v = e[u][i];
        if (!pre[v]) {
            ++child;
            int lowv = dfs(v, u);
            lowu = min(lowu, lowv);
            if (lowv >= pre[u])
                cut[u] = true;
        } else if (pre[v] < pre[u] && v != fa) {
            lowu = min(lowu, pre[v]);
        }
    }
    if (fa < 0 && child == 1) cut[u] = false;
    low[u] = lowu;
    return lowu;
}
