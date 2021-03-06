struct Edge { int u, v; };
stack<Edge> S;

int dfs(int u, int fa) {
	int lowu = pre[u] = ++clk;
	int child = 0;
	for (int v: e[u]) {
		Edge eg = (Edge){u, v};
		if (!pre[v]) {
			S.push(eg);
			++child;
			int lowv = dfs(v, u);
			lowu = min(lowu, lowv);
			if (lowv >= pre[u]) {
				iscut[u] = true;
				bcc_cnt++; bcc[bcc_cnt].clear();
				for (;;) {
					Edge x = S.top(); S.pop();
					if (bccno[x.u] != bcc_cnt) {
						bcc[bcc_cnt].push_back(x.u);
						bccno[x.u] = bcc_cnt;
					}
					if (bccno[x.v] != bcc_cnt) {
						bcc[bcc_cnt].push_back(x.v);
						bccno[x.v] = bcc_cnt;
					}
					if (x.u == u && x.v == v) break;
				}
			}
		} else if (pre[v] < pre[u] && v != fa) {
			S.push(eg);
			lowu = min(lowu, pre[v]);
		}
	}
	if (fa < 0 && child == 1) iscut[u] = 0;
	return lowu;
}

void find_bcc(int n) {
	memset(pre, 0, sizeof(pre));
	memset(iscut, 0, sizeof(iscut));
	memset(bccno, 0, sizeof(bccno));
	clk = bcc_cnt = 0;
	for (int i = 0; i < n; ++i)
		if (!pre[i])
			dfs(i, -1);
}
