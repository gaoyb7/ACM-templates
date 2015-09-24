int pre[maxn], low[maxn], sccno[maxn], clk, scc_cnt;
vector<int> e[maxn];
stack<int> S;

void dfs(int u) {
    pre[u] = low[u] = ++clk;
    S.push(u);
    for (size_t i = 0; i < e[u].size(); ++i) {
        int v = e[u][i];
        if (!pre[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if (!sccno[v]) {
            low[u] = min(low[u], pre[v]);
        }
    }
    if (low[u] == pre[u]) {
        scc_cnt++;
        while (1) {
            int x = S.top(); S.pop();
            sccno[x] = scc_cnt;
            if (x == u) break;
        }
    }
}

void find_scc(int n) {
    clk = scc_cnt = 0;
    memset(sccno, 0, sizeof(sccno));
    memset(pre, 0, sizeof(pre));
    for (int i = 0; i < n; ++i)
        if (!pre[i])
            dfs(i);
}
