int store_wagner() {
	int mincut = inf, tmp, k, pre, s = 1;
	memset(del, 0, sizeof(del));
	for (int t = 1; t < n; ++t) {
		for (int i = 1; i <= n; ++i)
			if (!del[i]) dist[i] = e[s][i];

		memset(vis, 0, sizeof(vis));
		vis[s] = true;
		k = s;
		for (int i = 1; i <= n - t; ++i) {
			tmp = -inf; pre = k; k = 0;
			for (int j = 1; j <= n; ++j) {
				if (!del[j] && !vis[j] && dist[j] > tmp) {
					k = j;
					tmp = dist[j];
				}
			}
			if (!k) return 0;
			vis[k] = true;
			for (int j = 1; j <= n; ++j)
				if (!del[j] && !vis[j])
					dist[j] += e[k][j];
		}
		mincut = min(mincut, dist[k]);
		del[k] = true;
		for (int i = 1; i <= n; ++i)
			if (!del[i] && i != pre) {
				e[pre][i] += e[k][i];
				e[i][pre] = e[pre][i];
			}
	}
	//if (mincut == inf) mincut = 0;
	return mincut;
}
